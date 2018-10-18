# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

In terms of the offical meaning from wikipedia, its: "a word invented by the president of the National Puzzlers' League as a synonym for the disease known as silicosis"
In terms of this pset, its the longest word allowed by the dictionary

## According to its man page, what does `getrusage` do?

"Get resource usage"

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

To calculate the time delta after processing the request

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

First, it only reads alphabetic characters and ' from a file, which it is reading character by character via fgetc().

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

You just want to get one character at a time for checking

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

To make them essentially read only
