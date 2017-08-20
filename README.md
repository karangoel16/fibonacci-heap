# fibonacci-heap HashTag Counter

it is implementation of fibonacci heap in CPP

What is hashtag?

"A hashtag is a type of metadata tag used on social network and microblogging services, that do not support real category meta data, which makes it possible for users to still find messages with a specific theme or content. Users create and use hashtags by placing the number sign or pound sign (colloquially known as the hash character # in reference to its resemblance to several slices or chops with a sharp implement) in front of a word or unspaced phrase, either in the main text of a message or at the end. Searching for that hashtag will yield each message that has been tagged with it. A hashtag archive is consequently collected into a single stream under the same hashtag.[1] For example, on the photo-sharing service Instagram, the hashtag #bluesky allows users to find all the posts that have been tagged using that hashtag."-wikipedia

What is fibonacci heap ?
Answer: 
Wikipedia
In computer science, a Fibonacci heap is a data structure for priority queue operations, consisting of a collection of heap-ordered trees. It has a better amortized running time than many other priority queue data structures including the binary heap and binomial heap. Michael L. Fredman and Robert E. Tarjan developed Fibonacci heaps in 1984 and published them in a scientific journal in 1987. They named Fibonacci heaps after the Fibonacci numbers, which are used in their running time analysis.

For the Fibonacci heap, the find-minimum operation takes constant (O(1)) amortized time.[1] The insert and decrease key operations also work in constant amortized time.[2] Deleting an element (most often used in the special case of deleting the minimum element) works in O(log n) amortized time, where n is the size of the heap.[2] This means that starting from an empty data structure, any sequence of a insert and decrease key operations and b delete operations would take O(a + b log n) worst case time, where n is the maximum heap size. In a binary or binomial heap such a sequence of operations would take O((a + b) log n) time. A Fibonacci heap is thus better than a binary or binomial heap when b is smaller than a by a non-constant factor. It is also possible to merge two Fibonacci heaps in constant amortized time, improving on the logarithmic merge time of a binomial heap, and improving on binary heaps which cannot handle merges efficiently.

It can keep track of million of hash tags and can be queried to provide n- popular hash tags. It is really fast algorithm to be implemented.
