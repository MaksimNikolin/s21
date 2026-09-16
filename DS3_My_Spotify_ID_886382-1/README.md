# MySpotify

## Recommender systems. Music recommendations

_Summary:_ This project introduces algorithms used for recommendation: non-personalized content-based collaborative filtering.

💡 [Tap here](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624) **to leave your feedback on the project**. It's anonymous and helps our team improve your educational experience. We recommend you complete the survey immediately after completing the project.

## Contents

1. [Chapter I](#chapter-i) \
   1.1. [Preamble](#preamble)
2. [Chapter II](#chapter-ii) \
   2.1. [Introduction](#introduction)
3. [Chapter III](#chapter-iii) \
   3.1. [Goals](#goals)
4. [Chapter IV](#chapter-iv) \
   4.1. [Instructions](#instructions)
5. [Chapter V](#chapter-v) \
   5.1. [Mandatory part](#mandatory-part)
6. [Chapter VI](#chapter-vi) \
   6.1. [Bonus part](#bonus-part)
7. [Chapter VII](#chapter-vii) \
   7.1. [Submission and peer-correction](#submission-and-peer-correction)

## Chapter I

How to learn at “School 21”:

- Here, you’ll find a unique learning experience with a lot of freedom. You’re given a task and left to find your own way to solve it, using whatever resources work best for you — whether that’s the Internet or AI tools like GigaChat. Just be mindful of information quality: verify, think critically, analyze, and compare.
- Peer-to-peer (P2P) learning is the exchange of knowledge and experience with peers, where everyone acts as both mentor and student. This approach allows you to gain a deeper understanding of the material by learning from one another.
- Feel free to ask for help: around you are peers who are also navigating this path for the first time. Share your own experience and ideas with others.  Join Rocket.Chat to stay updated with the latest community announcements. 
- Your learning is meaningless if you just copy someone else’s solutions. When receiving help from others, always make sure you fully understand the “why”, “how”, and “purpose” behind the solution. Don’t be afraid to make mistakes. 
- Does the task seem impossible? Take a break, get some fresh air and clear your mind — this has helped many people. Maybe after that, the solution will come to you naturally.
- The learning process is just as important as the result. It’s not just about completing the task — it’s about understanding HOW to solve it. 

### Preamble

Imagine what YouTube would look like without the recommendations section to the right of a video. How would Facebook look without its intelligent feed and the people you might know? What would Amazon be like without book recommendations? What would the media look like without the "Most popular" or "Most commented" or "Related news" section?

Recommendation systems are ubiquitous. Some of them have become the core of a product, some of them are just great features. Either way, they are important to products. Why is that?

Making choices is hard for people. It is a complicated cognitive task. Anything that can help us is useful. Even before the Internet, we used recommendations: friends, family, colleagues. When they recommended something to us, we considered it a valuable piece of information. Bestsellers in bookstores or blockbusters in movie theaters are another technique to help us make choices — to read or watch something that other people like. Even the power of brands is based on the problem of choice - build trust and do not ruin it, and a customer will buy your goods or services just because they do not want to solve the complicated problem.

Recommender systems are primarily useful for users and customers, but they are also a great tool for businesses: the algorithms help them increase revenues by up-selling or cross-selling goods that are appealing to users. It is a win-win situation, which is why recommendations are so valuable and important.

## Chapter II

### Introduction

What's under the hood of recommender systems? You are familiar with machine learning, but while recommendations can be made by applying some of these algorithms (by predicting a rating or predicting the likelihood that a user will click, like, or read), there are several specific approaches to this domain.

**Non-personalized recommendation systems**. They are useful when we do not know anything about a new user or customer. We can recommend to them something popular in different terms: bestsellers, blockbusters, most commented, most trending, most popular, Top 10 in the genre, etc. But to create such recommendations, we need data about how other users or customers made their choices. It is not very useful when you just start a new online store or media — cold start problem.

**Content-based recommendation systems**. To create this kind of recommendation we need to have some item descriptions: several paragraphs about books, short descriptions of goods, plots of movies, and so on. By comparing the descriptions, we can recommend similar items to a user. Another possibility is to create collections of similar items. It does not require any information about the user's past behavior, and it can be done in the case of starting something new from scratch.

**Collaborative filtering**. This is considered an advanced technique. In this case, we start making recommendations personally. Therefore, we need data about the past behavior of this particular user. The first approach, user-to-user, is that we recommend items that have been purchased by users similar to this particular user. The second approach, item-to-item, is that we recommend items that have similar profiles in terms of user behavior (e.g., suit and tie).

**Matrix factorizations** are considered part of collaborative filtering algorithms, but they use more advanced techniques: transforming the initial user-item matrix into a matrix of factors and making recommendations based on these latent factors (which can be genres, for example).

## Chapter III

### Goals

The goal of this project is to give you a first approach to recommender systems. You will try out all the approaches mentioned. At the same time, you will think about how to build a good product based on them. This will affect the metrics you use to evaluate your solutions.

## Chapter IV

### Instructions.

* This project will be evaluated by humans only. You are free to organize and name your files as you wish.
* Here and throughout, we use Python 3 as the only correct version of Python.
* The standard does not apply to this project. However, you are asked to be clear and structured in the design of your code.

## Chapter V

### Mandatory part

#### a. Task

In this project you will be working on a music recommendation system. There are tons of different songs and tracks. Your goal is to help users find something they like and play it on repeat! As we said, you will try different approaches to do this.

* Top 250 tracks. Non-personalized approach.
* Top 100 tracks by genre: Rock, Rap, Jazz, Electronic, Pop, Blues, Country, Reggae, New Age. Non-personalized approach.
* Collections: 50 songs about love, 50 songs about war, 50 songs about happiness, 50 songs about loneliness, 50 songs about money. Content-based approach.
* dataPeople similar to you listening: 10 recommendations for each user. Collaborative filtering approach.
* dataPeople who listen to this track usually listen to this track: 10 recommendations per track. Collaborative filtering.

#### b. Dataset

You are lucky and do not have to collect the dataset yourself. With the help of the data science community, you have access to parts of the [Million Songs Dataset](http://millionsongdataset.com/) (MSD):

*
    1. The Echo Nest Taste Profile Subset.

The format is the following (user_id, song_id, play_count) looks like this (tab-delimited):  
b80344d063b5ccb3212f76538f3d9e43d87dca9e  SOAKIMP12A8C130995  1   
b80344d063b5ccb3212f76538f3d9e43d87dca9e  SOAPDEY12A81C210A9  1   
b80344d063b5ccb3212f76538f3d9e43d87dca9e  SOBBMDR12A8C13253B  2

*
    2. The musiXmatch Dataset.

This file stored in a sparse format. It contains track_id, mxm_track_id, then word count for each of the top words, comma-separated. Word count is in sparse format `-> ...,<word idx>:<cnt>,... <word idx>` starts at 1 (not zero!).

*
    3. Tagtraum genre annotations for the Million Song Dataset.

This file contains 3 fields: track_id, majority_genre, minority_genre.

* The mapping between track ids and song ids.

The file contains 4 fields: track_id, song_id, artist, title. You can collect additional data if you find it useful for you.

> **Note:** You can find the dataset in the project page:
> 1. p02_train_triplets.txt.zip
> 2. p02_mxm_dataset_train.txt.zip
> 3. p02_msd_tagtraum_cd2.cls
> 4. p02_unique_tracks.txt

#### c. Implementation

In your research process, you can work in Jupyter notebooks. Then you need to organize your code into classes and methods. Finally, you will need to create a Python script that implements the recommendations above.

**Top 250 Tracks**

It should return a dataframe with the following fields: index number, artist name, track title, play count. The table should be sorted descending by play count.

**Top 100 tracks by genre**

For a given genre, return a dataframe with the following fields: index number, artist name, track title, play count. The table should be sorted descending by play count.

You should only use the main genre to perform the subtask.

**Collections**

For a given keyword (love, war, happiness), return a dataframe (50 tracks) with the following fields: index number, artist name, track title, play count. The table should be sorted descending by play count. Try different approaches for these recommendations:

* baseline — if you are looking for the keyword and the number of its occurrences in a song, filter with some threshold and then sort by the number of plays;
* word2vec — when you search not only for the keyword but also for several similar tokens using word2vec;
* classification task — you can label your data and try classification algorithms that predict for the other part of the dataset if a title belongs to a certain class.

You may find some other interesting ideas on how to make these recommendations better.

**People similar to you listening**

For these recommendations, you need to use the train/test split approach. In this case, the best practice is to cut a submatrix from the user-item matrix for the test dataset and use the other parts for the train.

To evaluate your recommendations, use the metric p@k (precision at k). It shows the percentage of correct recommendations from your list. It means that if you gave a user 10 tracks to listen to, and if they listened to 3 of them (they
actually listened to them in the test data set), then the p@k will be 30%. Calculate the average p@k for your recommendations. It should be at least greater than 10%.

The script should return 10 recommendations for a given user in a dataframe: index number, artist name, track title. The table should be sorted descending by the "likelihood" that a given user will "like" the track.

**People who listen to this track usually listen**

The same applies to these recommendations: use track/test split, use p@k. If you gave a user 10 tracks to listen to and they liked 3 of them (they really listen to them in the test dataset), then the p@k will be 30%. Calculate the average p@k for your recommendations. It should be at least greater than 10%.

The script should return 10 recommendations for a given track in a dataframe: index number, artist name, track title. The table should be sorted descending by the "likelihood" that a given user will "like" the track.

#### d. Submission

You will need to prepare two files for your repository: the Jupyter notebook in which you did your research, and the Python script. You may keep additional files there that you find useful for your program.

## Chapter VI

### Bonus Part

Visit any music streaming service (e.g., Spotify, Apple Music, Yandex Music, etc.), find 3 elements of their recommendation systems (it can be any recommendation block that you have not yet implemented), and repeat them in your project.

## Chapter VII

## Submission and peer connection

Submit your work to your Git repository as usual. Only the work on your repository will be graded.

Here are the points your peer reviewer will need to check:

* all 5 recommendation subsystems are present;
* all exceptions are handled;
* additional recommender elements from the bonus part have been added.
