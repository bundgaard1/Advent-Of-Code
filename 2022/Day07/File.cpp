#include <iostream>
#include <string>
#include <vector>
class Directory;

using namespace std;

class File {
   public:
    string name;

    int size;

    Directory* parentDirectory;

    File(string i_name, int i_size) {
        name = i_name;
        size = i_size;
    }
    ~File() { delete (this); }

    void print_file(int depth) {
        for (int i = 0; i < depth; i++) {
            cout << " ";
        }
        cout << "- " << this->name << "(file, size = " << this->size << ")\n";
    }
};

class Directory {
   public:
    // Children directories
    vector<Directory*> childDirectories;

    // Files in dicrectory
    vector<File*> files;

    Directory* parentDirectory;

    string name;

    int size;

    Directory(string i_name, Directory* i_parentName = NULL) {
        name = i_name;
        parentDirectory = i_parentName;
    }
    ~Directory() {
        for (int i = 0; i < childDirectories.size(); i++) {
            free(childDirectories.at(i));
        }
        for (int i = 0; i < files.size(); i++) {
            free(files.at(i));
        }
        free(this);
    }

    void push_file(File* f) {
        files.push_back(f);
        f->parentDirectory = this;
    }

    void push_directory(Directory* d) { childDirectories.push_back(d); }

    void print_directory(int depth) {
        for (int i = 0; i < depth; i++) {
            cout << " ";
        }
        cout << "- " << this->name << " (dir)\n";

        for (int i = 0; i < childDirectories.size(); i++) {
            Directory* d = childDirectories.at(i);
            d->print_directory(depth + 1);
        }
        for (int i = 0; i < files.size(); i++) {
            File* f = files.at(i);
            f->print_file(depth + 1);
        }

        return;
    }

    int dfs_size() {
        int sum = 0;
        for (int i = 0; i < childDirectories.size(); i++) {
            sum += childDirectories.at(i)->dfs_size();
        }
        for (int i = 0; i < files.size(); i++) {
            sum += files.at(i)->size;
        }
        this->size = sum;
        return sum;
    }

    void print_dir_sizes(int depth) {
        for (int i = 0; i < depth; i++) {
            cout << " ";
        }
        cout << "- " << this->name << " (size = " << this->size << ") \n";

        for (int i = 0; i < childDirectories.size(); i++) {
            childDirectories.at(i)->print_dir_sizes(depth + 1);
        }

        return;
    }

    int part1(int runningSum) {
        if (this->size < 100000) {
            runningSum += this->size;
        }
        for (int i = 0; i < childDirectories.size(); i++) {
            runningSum = childDirectories.at(i)->part1(runningSum);
        }

        return runningSum;
    }

    int part2(int smallest) {
        int spaceToFree = 389918;
        if (this->size > spaceToFree && this->size < smallest) {
            smallest = this->size;
        }

        for (int i = 0; i < childDirectories.size(); i++) {
            smallest = childDirectories.at(i)->part2(smallest);
        }
        return smallest;
    }
};