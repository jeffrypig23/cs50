def lines(a, b):
    """Return lines in both a and b"""

    # 0. Take in string inputs a and b
    # Those are provided in the arguments... :p

    # 1. Split each string into lines
    # http://docs.python.org/2/library/stdtypes.html#str.splitlines

    aSplit = a.splitlines()
    bSplit = b.splitlines()

    # Check to see if that worked
    #print("aSplit: {0}\nbSplit: {1}".format(aSplit, bSplit))

    # 2. Compute a list of all lines that appear in both a and b
    # https://docs.python.org/3/tutorial/datastructures.html

    # Emplty list to store the similar strings into
    similarList = []

    for aNumber in range(len(aSplit)):
        for bNumber in range(len(bSplit)):
            #print("Checking {0} against {1}".format(aSplit[aNumber], bSplit[bNumber]))
            if (aSplit[aNumber] == bSplit[bNumber]):
                similarList.append(aSplit[aNumber])
                #print("List so far: {}".format(similarList))

    # 3. Return the list
    # Be sure to remove duplicates from the list
    # https://docs.python.org/3/tutorial/datastructures.html#sets

    return list(set(similarList))


def sentences(a, b):
    """Return sentences in both a and b"""

    # 0. Take in string inputs a and b
    # a and b are already provided

    # 1. Split each string into sentences

    # Use nltk's sent_tokenize
    from nltk.tokenize import sent_tokenize

    # https://pythonspot.com/tokenizing-words-and-sentences-with-nltk/
    aSplit = sent_tokenize(a)
    bSplit = sent_tokenize(b)

    # 2. Compute a list of all sentences that appear in both a and b

    # Emplty list to store the similar strings into
    similarList = []

    for aNumber in range(len(aSplit)):
        for bNumber in range(len(bSplit)):
            if (aSplit[aNumber] == bSplit[bNumber]):
                similarList.append(aSplit[aNumber])

    # 3. Return the list
    # Be sure to remove duplicates from the list
    # https://docs.python.org/3/tutorial/datastructures.html#sets

    return list(set(similarList))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # 0. Take in string inputs a, b, and the substring lenght determined by n

    # 1. Split each string into all substrings of length n

    # Example:
    #   n = 3
    #   "Hello" -> ["Hel", "ell", "llo"]
    #
    # Other example:
    #   n = 2
    #   "Hello" -> ["He", "el", "ll", "lo"]

    # 1.1 Extract substring from string
    #   s[i:j] returns the substring of s from index i but not including index j

    aString = substringize(a, n)
    bString = substringize(b, n)

    # Emplty list to store the similar strings into
    similarList = []

    # Go through and compare strings
    for aNumber in range(len(aString)):
        for bNumber in range(len(bString)):
            if (aString[aNumber] == bString[bNumber]):
                similarList.append(aString[aNumber])

    # 3. Return the list
    # Be sure to remove duplicates from the blah blah blah... you know the drill :^)
    # https://docs.python.org/3/tutorial/datastructures.html#sets

    return list(set(similarList))


def substringize(string, length):

    # Create an empty array to store the substrings
    stringArray = []

    # Go through the string, and seperate it into substrings based on length
    for index in range(len(string) - length + 1):
        stringArray.append(string[index:index+length])

    # Returin the array, but with duplicates removed
    return list(set(stringArray))