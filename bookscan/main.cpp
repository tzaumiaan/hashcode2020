#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

struct lib {
    size_t id_;
    size_t books_;
    size_t sign_days_;
    size_t book_per_day_;
    size_t total_book_scores_;
    // score, id
    vector<pair<size_t, size_t> > sort_book_ids_by_scores_;
};

typedef struct lib lib;

double lib_core(const lib& cur_lib) {
    // example b
    // return 1*cur_lib.books_+10/cur_lib.sign_days_+100*cur_lib.book_per_day_;
    // return 1*cur_lib.books_+10000/cur_lib.sign_days_+0.1*cur_lib.book_per_day_+ 0*cur_lib.total_book_scores_;;

    // example c
    // return 1*cur_lib.books_+100000000/cur_lib.sign_days_+0.1*cur_lib.book_per_day_+0.00001*cur_lib.total_book_scores_/cur_lib.sort_book_ids_by_scores_.size();

    return 100*cur_lib.total_book_scores_+100000000/cur_lib.sign_days_+0.1*cur_lib.book_per_day_;
}

template <class T1, class T2, class Pred = std::less<T2> >
struct sort_pair_second {
    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
        Pred p;
        // return p(left.second, right.second);
        return p(left.first, right.first);
    }
};

int main() {
    uint64_t books, libs, days;
    unordered_map<size_t, size_t > book_ht;
    vector<pair<size_t , size_t> > book_scores;
    vector<lib> all_libs;
    vector<pair<double, size_t> > sort_libs;

    cin >> books >> libs >> days;
    all_libs.resize(libs);
    // cout << books << ", " << libs << ", " << days << std::endl;

    // parse scores for books
    for (size_t book_id = 0; book_id < books; book_id++) {
        size_t book_score;
        cin >> book_score;

        book_scores.push_back(std::make_pair(book_score, book_id));
        book_ht[book_id] = book_score;
        // cout << book_id << std::endl;
    }

    std::sort(book_scores.begin(), book_scores.end(), sort_pair_second<int, int, std::greater<int> >());

    // parse libraries
    for (size_t i = 0; i < libs; i++) {
        lib cur_lib;

        cur_lib.id_ = i;
        cur_lib.total_book_scores_ = 0;
        cin >> cur_lib.books_ >> cur_lib.sign_days_ >> cur_lib.book_per_day_;

        for (size_t j = 0; j < cur_lib.books_; j++) {
            size_t book_id;
            cin >> book_id;

            size_t book_score = book_ht[book_id];

            cur_lib.total_book_scores_ += book_score;

            cur_lib.sort_book_ids_by_scores_.push_back(std::make_pair(book_score, book_id));

            // cur_lib.book_ids_.push_back(book_id);
        }

        std::sort(cur_lib.sort_book_ids_by_scores_.begin(), cur_lib.sort_book_ids_by_scores_.end(), sort_pair_second<int, int, std::greater<int> >());

        double score = lib_core(cur_lib);

        all_libs[i] = cur_lib;
        sort_libs.push_back(std::make_pair(score, i));
    }

    std::sort(sort_libs.begin(), sort_libs.end(), sort_pair_second<int, int, std::greater<int> >());

    // Output file
    cout << libs << std::endl;

    for (size_t k = 0; k < sort_libs.size(); k++) {
        size_t cur_lib_id = sort_libs[k].second;
        lib cur_lib = all_libs[cur_lib_id];

        cout << cur_lib_id << " " << cur_lib.books_ << std::endl;

        for (size_t b = 0; b < cur_lib.sort_book_ids_by_scores_.size(); b++) {
            cout << cur_lib.sort_book_ids_by_scores_[b].second << " ";
        }

        cout << std::endl;
    }

    return 0;
}
