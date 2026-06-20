import requests
from bs4 import BeautifulSoup
import re
import json
from collections import Counter, defaultdict
from datetime import datetime

class Links:
    def __init__(self, path_to_the_file):
        self.links = []
        self.headers = {
            "User-Agent": (
                "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                "AppleWebKit/537.36 (KHTML, like Gecko) "
                "Chrome/122.0.0.0 Safari/537.36"
            )
        }

        with open(path_to_the_file, encoding='utf-8') as f:
            next(f)
            for line in f:
                movieId, imdbId, tmdbId = line.strip().split(',')
                self.links.append({
                    'movieId': int(movieId),
                    'imdbId': imdbId.zfill(7),
                    'tmdbId': tmdbId
                })

    @staticmethod
    def parse_runtime(duration):
        if not duration: return None
        match = re.match(r"PT(?:(\d+)H)?(?:(\d+)M)?", duration)
        if not match: return None
        hours = int(match.group(1)) if match.group(1) else 0
        minutes = int(match.group(2)) if match.group(2) else 0
        return hours * 60 + minutes


    def get_imdb(self, list_of_movies, list_of_fields):
        res = []

        for movie_id in list_of_movies:
            movie_data = next((l for l in self.links if l['movieId'] == movie_id), None)
            imdb_id = f"tt{movie_data['imdbId']}"
            url = f"https://www.imdb.com/title/{imdb_id}/"

            try:
                response = requests.get(url, headers=self.headers, timeout=5)
                soup = BeautifulSoup(response.text, "html.parser")
                script_tag = soup.find("script", type="application/ld+json")
                data = json.loads(script_tag.string)
                row = [movie_id]
                empty = True

                for field in list_of_fields:
                    if field == "Title": val = data.get("name")
                    elif field == "Year": val = data.get("datePublished", "").split("-")[0]
                    elif field == "Runtime": val = Links.parse_runtime(data.get("duration"))
                    elif field == "imdbRating": val = data.get("aggregateRating", {}).get("ratingValue")
                    else: val = None

                    if val: empty = False
                    row.append(val)
                if not empty: res.append(row)

            except Exception as e: print("Uvays Bakoev")

        return sorted(res, key=lambda x: x[0], reverse=True)


    def top_directors(self, n, limit=None):
        director_count = Counter()
        visited_ids = set()
        links_to_process = self.links[:limit] if limit else self.links

        for movie in links_to_process:
            imdb_id = f"tt{movie['imdbId']}"
            if imdb_id in visited_ids: continue
            visited_ids.add(imdb_id)

            url = f"https://www.imdb.com/title/{imdb_id}/"
            try:
                response = requests.get(url, headers=self.headers, timeout=5)
                soup = BeautifulSoup(response.text, "html.parser")
                script_tag = soup.find("script", type="application/ld+json")
                data = json.loads(script_tag.string)
                directors = data.get("director")

                if isinstance(directors, dict): names = [directors.get("name")]
                elif isinstance(directors, list): names = [d.get("name") for d in directors if "name" in d]
                else: names = []

                for name in names:
                    if name: director_count[name] += 1

            except Exception as e: print("Uvays Bakoev")

        return dict(director_count.most_common(n))


    def most_expensive(self, n, limit=None):
        movie_budgets = {}
        links_to_process = self.links[:limit] if limit else self.links

        for movie in links_to_process:
            imdb_id = f"tt{movie['imdbId']}"
            url = f"https://www.imdb.com/title/{imdb_id}/"
            try:
                response = requests.get(url, headers=self.headers, timeout=5)
                soup = BeautifulSoup(response.text, "html.parser")
                script_tag = soup.find("script", type="application/ld+json")
                data = json.loads(script_tag.string)
                title = data.get("name")

                budget_elem = soup.find(string=re.compile("Budget"))
                if budget_elem:
                    budget_text = budget_elem.find_next().text.strip()
                    match = re.search(r"\$([\d,]+)", budget_text)
                    if match:
                        budget = int(match.group(1).replace(",", ""))
                        movie_budgets[title] = budget

            except Exception as e: print("Uvays Bakoev")

        return dict(sorted(movie_budgets.items(), key=lambda x: x[1], reverse=True)[:n])


    def most_profitable(self, n, limit=None):
        movie_profits = {}
        links_to_process = self.links[:limit] if limit else self.links

        for movie in links_to_process:
            imdb_id = f"tt{movie['imdbId']}"
            url = f"https://www.imdb.com/title/{imdb_id}/"
            try:
                response = requests.get(url, headers=self.headers, timeout=5)
                soup = BeautifulSoup(response.text, "html.parser")
                script_tag = soup.find("script", type="application/ld+json")
                data = json.loads(script_tag.string)
                title = data.get("name")

                budget_elem = soup.find(string=re.compile("Budget"))
                if budget_elem:
                    budget_text = budget_elem.find_next().text.strip()
                    match = re.search(r"\$([\d,]+)", budget_text)
                    if match:
                        budget = int(match.group(1).replace(",", ""))

                gross_elem = soup.find(string=re.compile("Gross worldwide"))
                if gross_elem:
                    gross_text = gross_elem.find_next().text.strip()
                    match = re.search(r"\$([\d,]+)", gross_text)
                    if match: gross = int(match.group(1).replace(",", ""))

                profit = gross - budget
                movie_profits[title] = profit

            except Exception as e: print("Uvays Bakoev")

        return dict(sorted(movie_profits.items(), key=lambda x: x[1], reverse=True)[:n])

        
    def longest(self, n, limit=None):
        runtimes = {}
        links_to_process = self.links[:limit] if limit else self.links

        for movie in links_to_process:
            imdb_id = f"tt{movie['imdbId']}"
            url = f"https://www.imdb.com/title/{imdb_id}/"

            try:
                response = requests.get(url, headers=self.headers, timeout=5)
                soup = BeautifulSoup(response.text, "html.parser")
                script_tag = soup.find("script", type="application/ld+json")
                data = json.loads(script_tag.string)
                title = data.get("name")
                duration_str = data.get("duration")
                runtime = Links.parse_runtime(duration_str)

                if title and runtime:
                    runtimes[title] = runtime

            except Exception as e: print(f"Uvays Bakoev")

        return dict(sorted(runtimes.items(), key=lambda x: x[1], reverse=True)[:n])


    def top_cost_per_minute(self, n, limit=None):
        costs = {}
        links_to_process = self.links[:limit] if limit else self.links

        for movie in links_to_process:
            imdb_id = f"tt{movie['imdbId']}"
            url = f"https://www.imdb.com/title/{imdb_id}/"

            try:
                response = requests.get(url, headers=self.headers, timeout=5)
                soup = BeautifulSoup(response.text, "html.parser")
                script_tag = soup.find("script", type="application/ld+json")
                if not script_tag or not script_tag.string: continue
                data = json.loads(script_tag.string)
                title = data.get("name")
                duration_str = data.get("duration")
                runtime = Links.parse_runtime(duration_str)

                budget = None
                budget_elem = soup.find(string=re.compile("Budget"))
                if budget_elem:
                    budget_text = budget_elem.find_next().text.strip()
                    match = re.search(r"\$([\d,]+)", budget_text)
                    if match:
                        budget = int(match.group(1).replace(",", ""))

                if title and runtime is not None and budget is not None and runtime > 0:
                    cost_per_minute = round(budget / runtime, 2)
                    costs[title] = cost_per_minute

            except Exception as e: print(f"Uvays Bakoev")

        return dict(sorted(costs.items(), key=lambda x: x[1], reverse=True)[:n])


class Movies:
    def __init__(self, path_to_the_file):
        self.movies = []

        with open(path_to_the_file, encoding='utf-8') as f:
            next(f)
            for line in f:
                parts = line.strip().split(',')
                if len(parts) < 3: continue

                movieId = parts[0]
                title = ",".join(parts[1:-1])
                genres = parts[-1]

                self.movies.append({
                    'movieId': int(movieId),
                    'title': title,
                    'genres': genres
                })

    def dist_by_release(self):
        release_years = {}

        for movie in self.movies:
            title = movie['title']
            match = re.search(r'\((\d{4})\)', title)
            if match:
                year = int(match.group(1))
                if year in release_years:
                    release_years[year] += 1
                else:
                    release_years[year] = 1

        return dict(sorted(release_years.items(), key=lambda x: x[1], reverse=True))
   

    def dist_by_genres(self):
        genre_count = Counter()

        for movie in self.movies:
            genres = movie['genres'].split('|')
            genre_count.update(genres)

        return dict(sorted(genre_count.items(), key=lambda item: item[1], reverse=True))

        
    def dist_by_title_length(self):
        title_length_count = Counter()

        for movie in self.movies:
            title_length = len(movie['title'])
            title_length_count.update([title_length])

        return dict(sorted(title_length_count.items(), key=lambda item: item[1], reverse=True))


class Ratings:
    def __init__(self, path_to_the_file):
        self.path_to_the_file = 'data/'+ path_to_the_file
        self.data = []
        
        with open(self.path_to_the_file, 'r', encoding='utf-8') as file:
            header = file.readline().strip().split(',')
            for line in file:
                row = line.strip().split(',')
                row_dict = {
                    'userId': int(row[0]),
                    'movieId': int(row[1]),
                    'rating': float(row[2]),
                    'timestamp': int(row[3])
                }

                self.data.append(row_dict)

    class Movies:
        def __init__(self, ratings_instance, movies_file="data/movies.csv"):
            self.data = ratings_instance.data
            self.movie_titles = self.load_movie_titles(movies_file)

        def load_movie_titles(self, filepath):

            movie_titles = {}
            with open(filepath, 'r', encoding='utf-8') as f:
                lines = f.readlines()
                for line in lines[1:]:
                    row = line.strip().split(',')
                    movie_id = int(row[0])
                    title = row[1]
                    movie_titles[movie_id] = title
            return movie_titles
        
        def mean(self,values):
            return sum(values) / len(values) if values else 0

        def median(self,values):
            if not values:
                return 0
            sorted_values = sorted(values)
            n = len(sorted_values)
            mid = n // 2

            if n % 2 == 0:
                return (sorted_values[mid - 1] + sorted_values[mid]) / 2
            else:
                return sorted_values[mid]

        def dist_by_year(self):
            year_count = defaultdict(int)
            for row in self.data:
                year = datetime.fromtimestamp(row['timestamp']).year
                year_count[year] += 1
            
            return dict(sorted(year_count.items()))
        
        def dist_by_rating(self):
            ratings_count = defaultdict(int)
            for row in self.data:
                rating = row['rating']
                ratings_count[rating] += 1

            return dict(sorted(ratings_count.items()))
        
        def top_by_num_of_ratings(self, n):
            movie_ratings_count = defaultdict(int)
            for row in self.data:
                movie_id = row['movieId']
                movie_ratings_count[movie_id] += 1
            sorted_movies = sorted(movie_ratings_count.items(), key=lambda item: item[1], reverse=True)
            top_movies = {
                self.movie_titles.get(movie_id, "Unknown Movie"): count
                for movie_id, count in sorted_movies[:n]
            }

            return top_movies
        
        def top_by_ratings(self, n, metric=None):
            if metric is None:
                metric = self.mean

            movie_ratings = defaultdict(list)

            for row in self.data:
                movie_id = row['movieId']
                rating = row['rating']
                movie_ratings[movie_id].append(rating)

            movie_metrics = {}
            for movie_id, ratings in movie_ratings.items():
                score = metric(ratings)
                movie_metrics[movie_id] = round(score, 2)

            sorted_movies = sorted(movie_metrics.items(), key=lambda item: item[1], reverse=True)

            top_movies = {
                self.movie_titles.get(movie_id, "Unknown Movie"): score
                for movie_id, score in sorted_movies[:n]
            }

            return top_movies
        
        def top_controversial(self, n):
            movie_ratings = defaultdict(list)

            for row in self.data:
                movie_id = row['movieId']
                rating = row['rating']
                movie_ratings[movie_id].append(rating)

            movie_variances = {}
            for movie_id, ratings in movie_ratings.items():
                mean_rating = self.mean(ratings)  
                if len(ratings) > 1:
                    variance = sum((r - mean_rating) ** 2 for r in ratings) / len(ratings)
                else:
                    variance = 0  

                movie_variances[movie_id] = round(variance, 2)
            sorted_movies = sorted(movie_variances.items(), key=lambda item: item[1], reverse=True)
            top_movies = {
                self.movie_titles.get(movie_id, "Unknown Movie"): variance
                for movie_id, variance in sorted_movies[:n]
            }

            return top_movies
        
    class Users(Movies):    
        def __init__(self, ratings_instance, movies_file="data/movies.csv"):
            super().__init__(ratings_instance, movies_file)
            self.user_data = defaultdict(list)

            for row in self.data:
                self.user_data[row['userId']].append(row['rating'])

        def dist_by_num_of_ratings(self):
            rating_counts = defaultdict(int)

            for user_id, ratings in self.user_data.items():
                count = len(ratings)
                rating_counts[count] += 1

            return dict(sorted(rating_counts.items()))

        def dist_by_rating(self, metric=None):
            if metric is None:
                metric = self.mean
            user_rating_dist = defaultdict(int)

            for user_id, ratings in self.user_data.items():
                score = round(metric(ratings), 2)
                user_rating_dist[score] += 1

            return dict(sorted(user_rating_dist.items()))

        def top_controversial(self, n):
            user_variances = {}
            for user_id, ratings in self.user_data.items():
                if len(ratings) > 1:
                    mean_rating = self.mean(ratings)
                    variance = sum((r - mean_rating) ** 2 for r in ratings) / len(ratings)
                else:
                    variance = 0
                user_variances[user_id] = round(variance, 2)
            sorted_users = sorted(user_variances.items(), key=lambda x: x[1], reverse=True)
            return dict(sorted_users[:n])


class Tags:
    def __init__(self, path_to_the_file):
        self.path_to_the_file = 'data/'+ path_to_the_file
        self.data = []
        
        with open(self.path_to_the_file, 'r', encoding='utf-8') as file:
            header = file.readline().strip().split(',')

            for line in file:
                row = line.strip().split(',')
                row_dict = {
                    'userId': int(row[0]),
                    'movieId': int(row[1]),
                    'tag': str(row[2]),
                    'timestamp': int(row[3])
                }

                self.data.append(row_dict)

    def most_words(self, n):
        punctuation = '()[]{}:;.,!?-"\'1234567890'
        unique_tags = set(row['tag'] for row in self.data)
        tag_word_counts = {}

        for tag in unique_tags:
            cleaned_tag = ''.join(char if char not in punctuation else ' ' for char in tag)
            word_count = len([word for word in cleaned_tag.split() if word])
            tag_word_counts[tag] = word_count

        sorted_tags = sorted(tag_word_counts.items(), key=lambda x: x[1], reverse=True)
        return dict(sorted_tags[:n])

    def longest(self, n):
        unique_tags = set(row['tag'] for row in self.data)
        big_tags = sorted(unique_tags, key=len, reverse=True)
        big_tags = big_tags[:n]
        return big_tags

    def most_words_and_longest(self, n):
        most_word = list(self.most_words(n).keys())  
        longest = self.longest(n)
        result = [tag for tag in most_word if tag in longest]
        return result
        
    def most_popular(self, n):
        tag_counts = defaultdict(int)
        for row in self.data:
            tag = row['tag']
            tag_counts[tag]+=1
 
        sorted_tags = sorted(tag_counts.items(), key=lambda x: x[1], reverse=True)
        return dict(sorted_tags[:n])
        
    def tags_with(self, word):
        unique_tags = set(row['tag'] for row in self.data)
        tags_with_word = [tag for tag in unique_tags if word in tag]
        return sorted(tags_with_word)


class Tests:

    links = Links("data/links.csv")

    @staticmethod
    def test_get_imdb():
        result = Tests.links.get_imdb([1], ["Title", "Year", "Runtime", "imdbRating"])
        assert isinstance(result, list)
        assert isinstance(result[0], list)
        assert result[0][0] == 1

    @staticmethod
    def test_top_directors():
        result = Tests.links.top_directors(3, limit=10)
        assert isinstance(result, dict)
        assert len(result) <= 3
        for name, count in result.items():
            assert isinstance(name, str)
            assert isinstance(count, int)

    @staticmethod
    def test_most_expensive():
        result = Tests.links.most_expensive(2, limit=10)
        assert isinstance(result, dict)
        assert len(result) <= 2
        for title, budget in result.items():
            assert isinstance(title, str)
            assert isinstance(budget, int)

    @staticmethod
    def test_most_profitable():
        result = Tests.links.most_profitable(2, limit=10)
        assert isinstance(result, dict)
        assert len(result) <= 2
        for title, profit in result.items():
            assert isinstance(title, str)
            assert isinstance(profit, int)

    @staticmethod
    def test_links_longest():
        result = Tests.links.longest(2, limit=10)
        assert isinstance(result, dict)
        assert len(result) <= 2
        for title, runtime in result.items():
            assert isinstance(title, str)
            assert isinstance(runtime, int)

    @staticmethod
    def test_top_cost_per_minute():
        result = Tests.links.top_cost_per_minute(2, limit=10)
        assert isinstance(result, dict)
        assert len(result) <= 2
        for title, cost_per_minute in result.items():
            assert isinstance(title, str)
            assert isinstance(cost_per_minute, float)

    @staticmethod
    def test_dist_by_release():
        movies = Movies("data/movies.csv")
        movies.movies = [
            {'movieId': 1, 'title': 'Movie 1 (2022)', 'genres': 'Action'},
            {'movieId': 2, 'title': 'Movie 2 (2023)', 'genres': 'Comedy'},
            {'movieId': 3, 'title': 'Movie 3 (2022)', 'genres': 'Action'},
            {'movieId': 4, 'title': 'Movie 4 (2022)', 'genres': 'Action'},
            {'movieId': 5, 'title': 'Movie 5 (2023)', 'genres': 'Drama'},
        ]

        result = movies.dist_by_release()
        assert isinstance(result, dict)
        assert 2022 in result
        assert 2023 in result
        assert result[2022] == 3
        assert result[2023] == 2

    @staticmethod
    def test_dist_by_genres():
        movies = Movies("data/movies.csv")
        movies.movies = [
            {'movieId': 1, 'title': 'Movie 1 (2022)', 'genres': 'Action'},
            {'movieId': 2, 'title': 'Movie 2 (2023)', 'genres': 'Comedy'},
            {'movieId': 3, 'title': 'Movie 3 (2022)', 'genres': 'Action'},
            {'movieId': 4, 'title': 'Movie 4 (2022)', 'genres': 'Action'},
            {'movieId': 5, 'title': 'Movie 5 (2023)', 'genres': 'Drama'},
        ]

        result = movies.dist_by_genres()
        assert isinstance(result, dict)
        assert result['Action'] == 3
        assert result['Comedy'] == 1
        assert result['Drama'] == 1

    @staticmethod
    def test_dist_by_title_length():
        movies = Movies("data/movies.csv")
        movies.movies = [
            {'movieId': 1, 'title': 'Short', 'genres': 'Action'},
            {'movieId': 2, 'title': 'Medium Length', 'genres': 'Comedy'},
            {'movieId': 3, 'title': 'Longer Movie Title', 'genres': 'Action'},
            {'movieId': 4, 'title': 'Tiny', 'genres': 'Drama'},
            {'movieId': 5, 'title': 'Mid', 'genres': 'Action'},
        ]

        result = movies.dist_by_title_length()
        assert isinstance(result, dict)
        assert result[len('Short')] == 1
        assert result[len('Medium Length')] == 1
        assert result[len('Longer Movie Title')] == 1
        assert result[len('Tiny')] == 1
        assert result[len('Mid')] == 1

    @staticmethod
    def test_dist_by_year():
        mock_data = [
            {'userId': 1, 'movieId': 10, 'rating': 4.5, 'timestamp': 1609459200},  # 2021
            {'userId': 2, 'movieId': 11, 'rating': 3.0, 'timestamp': 1609459200},  # 2021
            {'userId': 3, 'movieId': 12, 'rating': 5.0, 'timestamp': 1577836800},  # 2020
        ]
        ratings = Ratings("ratings.csv")
        ratings.data = mock_data
        movies = Ratings.Movies(ratings)
        result = movies.dist_by_year()
        assert result == {2020: 1, 2021: 2}
        assert isinstance(result, dict)

    @staticmethod
    def test_dist_by_rating():
        mock_data = [
            {'userId': 1, 'movieId': 1, 'rating': 3.5, 'timestamp': 123},
            {'userId': 2, 'movieId': 2, 'rating': 3.5, 'timestamp': 123},
            {'userId': 3, 'movieId': 3, 'rating': 4.0, 'timestamp': 123},
        ]
        ratings = Ratings("ratings.csv")
        ratings.data = mock_data
        movies = Ratings.Movies(ratings)
        result = movies.dist_by_rating()
        assert result == {3.5: 2, 4.0: 1}
        assert isinstance(result, dict)

    @staticmethod
    def test_top_by_num_of_ratings():
        mock_data = [
            {'userId': 1, 'movieId': 101, 'rating': 4.0, 'timestamp': 0},
            {'userId': 2, 'movieId': 101, 'rating': 5.0, 'timestamp': 0},
            {'userId': 3, 'movieId': 102, 'rating': 3.0, 'timestamp': 0},
        ]
        ratings = Ratings("ratings.csv")
        ratings.data = mock_data
        movies = Ratings.Movies(ratings)
        movies.movie_titles = {101: "Movie A", 102: "Movie B"}
        result = movies.top_by_num_of_ratings(1)
        assert result == {"Movie A": 2}
        assert isinstance(result, dict)

    @staticmethod
    def test_top_by_ratings():
        mock_data = [
            {'userId': 1, 'movieId': 1, 'rating': 3, 'timestamp': 0},
            {'userId': 2, 'movieId': 1, 'rating': 5, 'timestamp': 0},
            {'userId': 3, 'movieId': 2, 'rating': 4, 'timestamp': 0},
        ]
        ratings = Ratings("ratings.csv")
        ratings.data = mock_data
        movies = Ratings.Movies(ratings)
        movies.movie_titles = {1: "Movie A", 2: "Movie B"}
        result = movies.top_by_ratings(1)
        assert result == {"Movie A": 4.0}
        assert isinstance(result, dict)

    @staticmethod
    def test_top_controversial():
        mock_data = [
            {'userId': 1, 'movieId': 1, 'rating': 1, 'timestamp': 0},
            {'userId': 2, 'movieId': 1, 'rating': 5, 'timestamp': 0},
            {'userId': 3, 'movieId': 2, 'rating': 3, 'timestamp': 0},
            {'userId': 4, 'movieId': 2, 'rating': 3, 'timestamp': 0},
        ]
        ratings = Ratings("ratings.csv")
        ratings.data = mock_data
        movies = Ratings.Movies(ratings)
        movies.movie_titles = {1: "Movie X", 2: "Movie Y"}
        result = movies.top_controversial(1)
        assert result == {"Movie X": 4.0}
        assert isinstance(result, dict)

    @staticmethod
    def test_user_dist_by_num_of_ratings():
        ratings = Ratings("ratings.csv")
        ratings.data = [
            {'userId': 1, 'movieId': 1, 'rating': 4.0, 'timestamp': 0},
            {'userId': 1, 'movieId': 2, 'rating': 3.0, 'timestamp': 0},
            {'userId': 2, 'movieId': 1, 'rating': 5.0, 'timestamp': 0},
        ]
        users = Ratings.Users(ratings)
        result = users.dist_by_num_of_ratings()
        assert result == {2: 1, 1: 1}
        assert isinstance(result, dict)

    @staticmethod
    def test_user_dist_by_rating():
        ratings = Ratings("ratings.csv")
        ratings.data = [
            {'userId': 1, 'movieId': 1, 'rating': 4.0, 'timestamp': 0},
            {'userId': 1, 'movieId': 2, 'rating': 5.0, 'timestamp': 0},
            {'userId': 2, 'movieId': 3, 'rating': 3.0, 'timestamp': 0},
        ]
        users = Ratings.Users(ratings)
        result = users.dist_by_rating()
        assert result == {4.5: 1, 3.0: 1}
        assert isinstance(result, dict)

    @staticmethod
    def test_user_top_controversial():
        ratings = Ratings("ratings.csv")
        ratings.data = [
            {'userId': 1, 'movieId': 1, 'rating': 1.0, 'timestamp': 0},
            {'userId': 1, 'movieId': 2, 'rating': 5.0, 'timestamp': 0},
            {'userId': 2, 'movieId': 3, 'rating': 3.0, 'timestamp': 0},
        ]
        users = Ratings.Users(ratings)
        result = users.top_controversial(1)
        assert result == {1: 4.0}
        assert isinstance(result, dict)

    @staticmethod
    def test_most_words():
        tags = Tags("tags.csv")
        tags.data = [
            {'userId': 1,'movieId':2,'tag':'it is like dark paradise','timestamp': '1445714992'},
            {'userId': 2,'movieId':3,'tag':'you should, could, must do that', 'timestamp': '1325714992'},
            {'userId': 3,'movieId':4,'tag':'shame is taking only','timestamp': '1445714992'}
            ]

        result = tags.most_words(1)
        assert result == {'you should, could, must do that': 6}
        assert isinstance(result, dict)
        
    @staticmethod
    def test_longest():
        tags = Tags("tags.csv")
        tags.data = [
            {'userId': 1,'movieId':2,'tag':'it is like a dark paradise','timestamp': '1445714992'},
            {'userId': 2,'movieId':3,'tag':'vague - not clearly expressed, known, described, or decided', 'timestamp': '1325714992'},
            {'userId': 3,'movieId':4,'tag':'shame is taking only','timestamp': '1445714992'}
            ]
        result = tags.longest(2)
        assert result == ["vague - not clearly expressed, known, described, or decided","it is like a dark paradise"]
        assert isinstance(result, list)

    @staticmethod
    def test_most_words_and_longest():
        tags = Tags('tags.csv')
        tags.data = [
            {'userId': 12,'movieId':2,'tag':"Never listen to the no's",'timestamp': '1445712992'},
            {'userId': 223,'movieId':4,'tag':'And the only thin I know is to love what I\'m doing', 'timestamp': '1321714992'},
            {'userId': 32,'movieId':6,'tag':'Life ain\'nt really what it seems','timestamp': '1445714932'}
            ]
        result = tags.most_words_and_longest(2)
        assert result == ['And the only thin I know is to love what I\'m doing','Life ain\'nt really what it seems']
        assert isinstance(result, list)

    @staticmethod
    def test_most_popular():
        tags = Tags('tags.csv')
        tags.data = [
            {'userId': 12,'movieId':2,'tag':"Never listen to the no's",'timestamp': '1445712992'},
            {'userId': 223,'movieId':3,'tag':'And the only thin I know is to love what I\'m doing', 'timestamp': '1321714992'},
            {'userId': 32,'movieId':6,'tag':'Never listen to the no\'s','timestamp': '1445714932'}
            ]
        result = tags.most_popular(2)
        assert result == {"Never listen to the no's": 2, "And the only thin I know is to love what I'm doing": 1}
        assert isinstance(result, dict)

    @staticmethod
    def test_tags_with():
        tags = Tags('tags.csv')
        tags.data = [
            {'userId': 12,'movieId':2,'tag':"you should, could, must do that",'timestamp': '1445712992'},
            {'userId': 23,'movieId':3,'tag':'And the only thin I know is to love what I\'m doing', 'timestamp': '1321714992'},
            {'userId': 1,'movieId':1,'tag':'what are you waiting for?','timestamp': '1445714932'}
            ]
        result = tags.tags_with('you')
        assert result == ['what are you waiting for?','you should, could, must do that']
        assert isinstance(result, list)

if __name__ == "__main__":

    Tests.test_get_imdb()
    Tests.test_top_directors()
    Tests.test_most_expensive()
    Tests.test_most_profitable()
    Tests.test_links_longest()
    Tests.test_top_cost_per_minute()

    Tests.test_dist_by_release()
    Tests.test_dist_by_genres()
    Tests.test_dist_by_title_length()

    Tests.test_dist_by_year()
    Tests.test_dist_by_rating()
    Tests.test_top_by_num_of_ratings()
    Tests.test_top_by_ratings()
    Tests.test_top_controversial()
    Tests.test_user_dist_by_num_of_ratings()
    Tests.test_user_dist_by_rating()
    Tests.test_user_top_controversial()

    Tests.test_most_words()
    Tests.test_longest()
    Tests.test_most_words_and_longest()
    Tests.test_most_popular()
    Tests.test_tags_with()
