#pragma once
#include "Win.hpp"
#include "Observer.hpp"
#include <list>

using namespace std;

class WinMan: public Observer {
public:
    void add_win(Win *win) {
        win->add_observer(this, "set_z");
        insert_win(win);
    }
    void remove_win(Win *win) {
        win->remove_observer(this, "set_z");// Finish this

    }
    virtual void on_notify(Subject *the_subject, string the_event) {
        if (the_event == "set_z") {
            list<Win*>::iterator it = find_win(dynamic_cast<Win*>(the_subject));
            Win *tmp = *it;
            windows.erase(it);
            insert_win(tmp);
        }
    }
private:
    void insert_win(Win *win) {
        if (windows.empty()) {
            windows.push_back(win);
        } else {
            list<Win*>::iterator it = windows.begin();
            while (it->get_z() < win->get_z() && it < windows.end()) it++;
            if (it->get_z() >= win->get_z()) {
                windows.insert(it, win);
            } else {
                windows.push_back(win);
            }
        }
    }
    list<Win*>::iterator find_win(Win *win) {
        list<Win*>::iterator it;
        for (it = windows.begin(); it != windows.end(); it++) {
            if (dynamic_cast<Subject*>(*it) == the_subject) {
                break;
            }
        
        }
        return it;
    }
    list<Win*> windows;
};
