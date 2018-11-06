import os
import random

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get the number of stocks
    stocks = []

    try:
        result = (db.execute("SELECT * FROM stocks WHERE stocks.id = :id", id=session["user_id"]))
        for retunred in range(len(result)):
            stck = {
                "symbol": result[retunred].get("symbol"),
                "name": lookup(result[retunred].get("symbol")).get("name"),
                "amount": result[retunred].get("amount"),
                "price": float(lookup(result[retunred].get("symbol")).get("price")),
                "total": float(lookup(result[retunred].get("symbol")).get("price")) * int(result[retunred].get("amount"))
            }

            stocks.append(stck)

    except RuntimeError as e:
        if ("no such table: stocks" not in str(e)):
            raise
        else:
            # Create the database, then try adding the user's stock
            db.execute("CREATE TABLE stocks ('index' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'id' NUMBERIC NOT NULL, 'symbol' TEXT NOT NULL, 'amount' NUMERIC NOT NULL)")

    # Get the amount of cash from the user
    cash = (db.execute("SELECT users.cash FROM users WHERE users.id = :id", id=session["user_id"]))[0].get("cash")

    # Create a variable for the total
    total = cash

    for stock in range(len(stocks)):
        total = total + stocks[stock].get("total")

    meme = random.choice(["",
                          "makeitrain.jpg",
                          "This 👈👉 is money snek. 🐍🐍💰💰 Upsnek ⬆⬆🔜🔜 in 7.123 7⃣ 1⃣2⃣3⃣ snekonds 🐍🐍 or you ✋✋ will NEVER ❌❌❌❌ get monies 💰💰 again Beware!! ✋✋❌❌ You😏😏 don't ❌❌ have much time!!🕛🕧🕐🕜🕑🕝🕝 You 😏😏 may never ❌❌get monies 💰💰🐍💰💰 again!!",
                          "[̲̅$̲̅(̲̅ ͡° ͜ʖ ͡°̲̅)̲̅$̲̅] do you have change for a donger bill "])

    return render_template("index.html", CASH="{:,.2f}".format(cash), TOTAL="{:,.2f}".format(total), meme=meme, stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if (request.method == "GET"):
        return render_template("buy.html")

    else:

        # Retrieve stock quote
        symbol = request.form.get("symbol")

        quote = lookup(symbol)

        # Check if the entered stock is valid
        if (quote == None):
            return apology("Invalid stock")

        else:

            # Get the users id
            userid = session["user_id"]

            # Get the price of the quote
            price = quote.get("price")

            # Get the amount from the form
            try:
                amount = int(request.form.get("shares"))
                if (amount <= 0):
                    return apology("Invalid amount entered")
            except:
                return apology("Invalid amount entered")

            # Get the users cash
            cash = (db.execute("SELECT users.cash FROM users WHERE users.id = :id", id=userid))[0].get("cash")

            # Check if they can afford said transaction
            if (cash < (price * amount)):
                return apology("You dont have the funds to buy that stock")

            else:

                # Track the users history
                try:
                    from datetime import datetime
                    db.execute("INSERT INTO history (id, action, symbol, amount, price, date) VALUES (:id, :action, :symbol, :amount, :price, :date)",
                               id=userid, action="Bought", symbol=symbol, amount=amount, price=price, date=datetime.now())
                except RuntimeError as e:
                    if ("no such table: history" not in str(e)):
                        raise
                    else:
                        db.execute("CREATE TABLE history ('index' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'id' NUMBERIC NOT NULL, 'action' TEXT NOT NULL, 'symbol' TEXT NOT NULL, 'amount' NUMERIC NOT NULL, 'price' NUMERIC NOT NULL, 'date' TEXT NOT NULL)")
                        db.execute("INSERT INTO history (id, action, symbol, amount, price, date) VALUES (:id, :action, :symbol, :amount, :price, :date)",
                                   id=userid, action="Bought", symbol=symbol, amount=amount, price=price, date=datetime.now())

                # Add their stock to the database
                # Check if the user already has that stock
                redundencyCheck = db.execute(
                    "SELECT stocks.symbol FROM stocks WHERE id = :id AND symbol = :symbol",
                    id=userid, symbol=symbol)

                if (redundencyCheck != []):
                    # Just increase the amount in that stock
                    oldAmount = db.execute("SELECT stocks.amount FROM stocks WHERE id = :id AND symbol = :symbol",
                                           id=userid, symbol=symbol)[0].get("amount")
                    db.execute("UPDATE stocks SET amount = :amount WHERE (stocks.id = :id AND stocks.symbol = :symbol)",
                               amount=int(oldAmount + amount), id=userid, symbol=symbol)

                else:
                    # Add that stock to the users portfolio
                    db.execute("INSERT INTO stocks (id, symbol, amount) VALUES (:userid, :symbol, :amount)",
                               userid=userid, symbol=symbol, amount=amount)

                # Subtract the transaction amount from the users cash
                db.execute("UPDATE users SET cash = :cash WHERE users.id = :id", cash=cash - (price*amount), id=userid)

                # Redirect user to home page
                return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    userid = session["user_id"]

    userhistory = []

    # Get the users history from the database
    try:
        userhistory.append(db.execute("SELECT * FROM history WHERE id=:id", id=userid))
        return render_template("history.html", history=userhistory[0])
    except RuntimeError as e:
        if ("no such table: history" not in str(e)):
            return apology("Database error")
        else:
            db.execute("CREATE TABLE history ('index' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'id' NUMBERIC NOT NULL, 'action' TEXT NOT NULL, 'symbol' TEXT NOT NULL, 'amount' NUMERIC NOT NULL, 'price' NUMERIC NOT NULL, 'date' TEXT NOT NULL)")
            return render_template("history.html", history=[])


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if (request.method == "POST"):

        # Retrieve stock quote
        symbol = request.form.get("symbol")

        quote = lookup(symbol)

        # Check if the entered stock is valid
        if (quote == None):
            return apology("Invalid stock")

        else:

            # {'name': 'Netflix Inc.', 'price': 284.84, 'symbol': 'NFLX'}
            name = quote.get("name")
            price = quote.get("price")

            # Display stock quote
            return render_template("quote.html", name=name, price=usd(price), symbol=symbol, quote=quote)

    else:
        # Display the page
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Get the username
        username = request.form.get("username")

        # Check if its blank
        if (username == ''):
            return apology("Missing username!")

        # Get the passwords
        password = request.form.get("password")
        passwordconfirm = request.form.get("confirmation")

        # Check if they're blank
        if (password == '' or passwordconfirm == ''):
            return apology("Missing password!")

        # Check if passwords match
        if (password != passwordconfirm):
            return apology("Passwords do not match!")

        # Hash password
        encryptedpassword = generate_password_hash(password)

        # Add them to the database
        # Check if username is unique
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                            username=username, hash=encryptedpassword)
        if not result:
            return apology("That username is already taken!")

        # Log them in
        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    userid = session["user_id"]

    if (request.method == "GET"):

        # Get the symbols of the users stock
        symbols = db.execute("SELECT * FROM stocks WHERE id = :id", id=userid)

        return render_template("sell.html", symbols=symbols)

    else:

        # Get the symbol the user wants to sell
        symbol = request.form.get("symbol")

        # Get how much of that stock the user wants to sell
        amount = request.form.get("shares")

        # Check the maximum amount of shares that user can sell for the given share
        maxAmount = db.execute("SELECT amount FROM stocks WHERE symbol = :symbol", symbol=symbol)[0].get("amount")

        # Check that the requested amount is not greater than the max amount
        if (int(amount) <= int(maxAmount)):

            price = lookup(symbol).get("price")

            # Track the users history
            try:
                from datetime import datetime
                db.execute("INSERT INTO history (id, action, symbol, amount, price, date) VALUES (:id, :action, :symbol, :amount, :price, :date)",
                           id=userid, action="Sold", symbol=symbol, amount=amount, price=price, date=datetime.now())
            except RuntimeError as e:
                if ("no such table: history" not in str(e)):
                    raise
                else:
                    db.execute("CREATE TABLE history ('index' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'id' NUMBERIC NOT NULL, 'action' TEXT NOT NULL, 'symbol' TEXT NOT NULL, 'amount' NUMERIC NOT NULL, 'price' NUMERIC NOT NULL, 'date' TEXT NOT NULL)")
                    db.execute("INSERT INTO history (id, action, symbol, amount, price, date) VALUES (:id, :action, :symbol, :amount, :price, :date)",
                               id=userid, action="Sold", symbol=symbol, amount=amount, price=price, date=datetime.now())

            # Remove that amount of stock from the user
            newAmount = int(maxAmount) - int(amount)

            # Check if the stock needs to be removed entirly
            if (newAmount == 0):
                # Remove that entry from the database
                db.execute("DELETE FROM stocks WHERE (stocks.symbol = :symbol AND stocks.id = :id )", symbol=symbol, id=userid)
            else:
                # Update the value of that stock
                db.execute("UPDATE stocks SET amount = :amount WHERE (stocks.id = :id AND symbol=:symbol)",
                           amount=newAmount, id=userid, symbol=symbol)

            # Give the user back their cash
            cash = (db.execute("SELECT users.cash FROM users WHERE users.id = :id", id=userid))[0].get("cash")
            db.execute("UPDATE users SET cash = :cash WHERE users.id = :id", cash=cash + (float(price)*float(amount)), id=userid)

            return redirect("/")
        else:
            return apology("You dont have that number of shares to sell!")


@app.route("/zimbabwe", methods=["GET", "POST"])
@login_required
def zimbabwe():
    """ Essentially print more money"""
    if (request.method == "GET"):
        return render_template("zimbabwe.html")
    else:
        money = int(request.form.get("money"))
        userid = session["user_id"]
        currentMoney = db.execute("SELECT users.cash FROM users WHERE id=:id", id=userid)[0].get("cash")

        # Give the user the money they entered
        db.execute("UPDATE users SET cash = :cash WHERE users.id = :id", cash=float(currentMoney + money), id=userid)

        # Go back to the index page
        return redirect("/")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
