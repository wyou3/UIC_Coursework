//
// Netflix Movie Review Analysis
//
// Woong Jin You
// U. of Illinois, Chicago
// CS341, Fall 2016
// HW #02
//

#include <iostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <complex>
#include <limits>
#include <ctime>

using namespace std;

class Movie;
class Review;
class User;

vector<Movie> inputMovies(string fileName);
vector<Review> inputReviews(string fileName);
vector<User> find_users(vector<Review> reviews);
void top_10_movies(vector<Review> & reviews, vector<Movie> & movies);
void top_10_users(vector<User> & users);
void movie_info(vector<Movie> & movies);

int main(){

    vector<Movie> movies = inputMovies("movies.csv");
    vector<Review> reviews = inputReviews("reviews.csv");

    vector<User> users = find_users(reviews);

    cout << "** Netflix Movie Review Analysis **" << endl << endl;

    top_10_movies(reviews, movies);
    top_10_users(users);

    movie_info(movies);

    return 0;
}

/* ----------------------------------------------------------------- */
// classes
/* ----------------------------------------------------------------- */
class Movie
{
public:
    int  MovieID, PubYear, reviews = 0, ratingTotal = 0;
    int one=0,two=0,three=0,four=0,five=0;
    double avg = 0;
    string  MovieName;

    Movie(int movieID, string movieName, int pubYear)
    : MovieID(movieID), MovieName(movieName), PubYear(pubYear)
    { }
    Movie(){}
};

class Review
{
public:
    int  MovieID, UserID, Rating;
    string  ReviewDate;

    Review(int movieID, int userID, int rating, string reviewDate)
    : MovieID(movieID), UserID(userID), Rating(rating), ReviewDate(reviewDate)
    { }
};

class User
{
public:
    int UserID;
    int Reviews;

    User(int userID, int reviews)
    : UserID(userID), Reviews(reviews)
    { }
};
/* ----------------------------------------------------------------- */
// end classes
/* ----------------------------------------------------------------- */


/* ----------------------------------------------------------------- */
// input functions
/* ----------------------------------------------------------------- */
vector<Movie> inputMovies(string fileName){
    string  line, movieID, movieName, pubYear;
    int movieCount = 0;
    ifstream  moviesFile(fileName);

    vector<Movie> movies;

    if (!moviesFile.good())
    {
        cout << "cannot open movies file!" << endl;
        return movies;
    }
    
    cout << ">> Reading movies... ";

    getline(moviesFile, line);  // skip header row:

    while (getline(moviesFile, line))
    {
        movieCount++;

        stringstream  ss(line);

        getline(ss, movieID, ',');
        getline(ss, movieName, ',');
        getline(ss, pubYear);

        Movie M(stoi(movieID), movieName, stoi(pubYear));
        movies.push_back(M);
    }

    cout << movieCount << endl;
    return movies;
}

vector<Review> inputReviews(string fileName){
    vector<Review> reviews;
    string line, movieID, userID, rating, reviewDate;
    int reviewCount = 0;
    ifstream reviewsFile(fileName);
    
    cout << ">> Reading reviews... ";
    
    if (!reviewsFile.good())
    {
        cout << "cannot open reviews file!" << endl;
        return reviews;
    }

    getline(reviewsFile, line);  // skip header row:

    while (getline(reviewsFile, line))
    {
        reviewCount++;

        stringstream  ss(line);

        getline(ss, movieID, ',');
        getline(ss, userID, ',');
        getline(ss, rating, ',');
        getline(ss, reviewDate);

        Review R(stoi(movieID), stoi(userID), stoi(rating), reviewDate);
        reviews.push_back(R);
    }

    cout << reviewCount << endl << endl;
    return reviews;
}

vector<User> find_users(vector<Review> reviews){
    vector<User> users;
    bool flag;
    int RID,i,j;

    sort(
        reviews.begin(), 
        reviews.end(), 
        [](const Review& r1, const Review& r2)
        {
        //
        // in ascending order by movieID code:
        //
            if (r1.UserID < r2.UserID)
                return true;
            else
                return false;
        }
        );

    //find and store all users 
    for(i=0; i<reviews.size(); i++){
        RID = reviews[i].UserID;
        User U(RID, 0);
        users.push_back(U);

        if(reviews.size() > i){
            while(RID == reviews[i].UserID){
                users[users.size()-1].Reviews++;
                i++;
            }
            i--;
        }
    }

    return users;
}
/* ----------------------------------------------------------------- */
// end input functions
/* ----------------------------------------------------------------- */


/* ----------------------------------------------------------------- */
// search and display functions
/* ----------------------------------------------------------------- */
void top_10_movies(vector<Review> & reviews, vector<Movie> & movies){
    int MID,i,j;

    cout << ">> Top-10 Movies <<" <<endl << endl;

    //sort reviews by movieID
    sort(
        reviews.begin(), 
        reviews.end(), 
        [](const Review& r1, const Review& r2)
        {
        //
        // in ascending order by movieID code:
        //
            if (r1.MovieID < r2.MovieID)
                return true;
            else
                return false;
        }
        );

    //find averages 
    for(i=0; i<reviews.size(); i++){
        j = 0;
        MID = reviews[i].MovieID;

        vector<Movie>::iterator m = find_if(movies.begin(), movies.end(), 
            [&](const Movie & m) -> bool { return m.MovieID == MID;});

        while(reviews[i].MovieID == MID){
            m->reviews++;
            m->ratingTotal += reviews[i].Rating;
            switch(reviews[i].Rating){
                case 1: 
                m->one++;
                break;
                case 2:
                m->two++;
                break;
                case 3:
                m->three++;
                break;
                case 4:
                m->four++;
                break;
                case 5:
                m->five++;
                break;
            }
            i++;
        }
        i--;
    }

    //calculate avg
    for(i=0; i<movies.size(); i++)
        movies[i].avg = (double)movies[i].ratingTotal/(double)movies[i].reviews;

    //sort movies by their average ratings
    sort(
        movies.begin(), 
        movies.end(), 
        [](const Movie& m1, const Movie& m2)
        {
        //
        // in ascending order by movie AVG rating:
        //
            if (m1.avg > m2.avg)
                return true;
            else
                return false;
        }
        );

    //display top 10 movies
    cout.precision(6);
    cout << left << setw(10) << "Rank" << setw(10) << "ID" << setw(13) << "Reviews" << setw(15) << "Avg" << setw(35) << "Name" <<endl;
    for(i=0; i<10; i++)
        cout << left << setw(10) << i+1 << setw(10) << movies[i].MovieID << setw(13) << movies[i].reviews << setw(15) << movies[i].avg << setw(35) << movies[i].MovieName << endl;
}

void top_10_users(vector<User> & users){

    //sort Users by number of reviews 
    sort(
        users.begin(), 
        users.end(), 
        [](const User& u1, const User& u2)
        {
        //
        // in ascending order by num reviews:
        //
            if (u1.Reviews > u2.Reviews)
                return true;
            else if(u1.Reviews < u2.Reviews)
                return false;
            else {
                if(u1.UserID < u2.UserID)
                    return true;
                else 
                    return false;
            }
        }
        );

    //display top ten active users
    cout << endl << ">> Top-10 Users <<" << endl << endl;
    cout << left << setw(10) << "Rank" << setw(10) << "ID" << setw(10) << "Reviews" << endl;
    for(int i=0; i<10; i++)
        cout << left << setw(10) << i+1 << setw(15) << users[i].UserID << setw(15) << users[i].Reviews << endl;
}

void movie_info(vector<Movie> & movies){
    int MID, i;
    cout << endl << ">> Movie Information << " << endl << endl;

    MID = 1;
    while(MID){
        cout << "Please enter a movie ID [1...250], 0 to stop: ";
        cin >> MID;
        
        if((int)MID < 1 || (int)MID > movies.size()){
            cout << "** Invalid movie id, please try again..." <<endl;
        }else{

         i=0;
         vector<Movie>::iterator m = find_if(movies.begin(), movies.end(), 
            [MID](const Movie & m) -> bool { return m.MovieID == MID;});

         cout << "Movie:        '" <<  m->MovieName << "'" << endl;
         cout << "Year:          " <<  m->PubYear << endl;  
         cout << "Avg rating :   " <<  m->avg << endl;
         cout << "Num reviews:   " <<  m->reviews << endl;
         cout << "Num 1's:       " <<  m->one << endl;
         cout << "Num 2's:       " <<  m->two << endl;
         cout << "Num 3's:       " <<  m->three << endl;
         cout << "Num 4's:       " <<  m->four << endl;
         cout << "Num 5's:       " <<  m->five << endl << endl;
     }
 }
}
/* ----------------------------------------------------------------- */
// end search and display functions
/* ----------------------------------------------------------------- */
