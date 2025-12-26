#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>   
using namespace std;
#define LONG_MAX 9223372036854775807
void printMatrix(vector<vector<long long>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void maintainInsert(vector<vector<long long>> &matrix, int currentRow, int currentCol){
    int row = matrix.size();
    int col = matrix[0].size();
    if(currentRow - 1 >= 0 && currentCol - 1 >= 0){
        if(matrix[currentRow - 1][currentCol] >= matrix[currentRow][currentCol] && matrix[currentRow - 1][currentCol] >= matrix[currentRow][currentCol - 1]){
            swap(matrix[currentRow][currentCol], matrix[currentRow - 1][currentCol]);
            // printMatrix(matrix);
            maintainInsert(matrix, currentRow - 1, currentCol);
        }
        else if(matrix[currentRow][currentCol - 1] >= matrix[currentRow][currentCol] && matrix[currentRow][currentCol - 1] >= matrix[currentRow - 1][currentCol]){
            swap(matrix[currentRow][currentCol], matrix[currentRow][currentCol - 1]);
            // printMatrix(matrix);
            maintainInsert(matrix, currentRow, currentCol - 1);
        }
        else{
            return;
        }
    }
    else if(currentRow - 1 >= 0){
        if(matrix[currentRow - 1][currentCol] >= matrix[currentRow][currentCol]){
            swap(matrix[currentRow][currentCol], matrix[currentRow - 1][currentCol]);
            // printMatrix(matrix);
            maintainInsert(matrix, currentRow - 1, currentCol);
        }
        else{
            return;
        }
    }
    else if(currentCol - 1 >= 0){
        if(matrix[currentRow][currentCol - 1] >= matrix[currentRow][currentCol]){
            swap(matrix[currentRow][currentCol], matrix[currentRow][currentCol - 1]);
            // printMatrix(matrix);
            maintainInsert(matrix, currentRow, currentCol - 1);
        }
        else{
            return;
        }
    }
    else{
        return;
    }
}

void maintainExtract(vector<vector<long long>> &matrix, int currentRow, int currentCol){
    int row = matrix.size();
    int col = matrix[0].size();
    if(currentRow + 1 < row && currentCol + 1 < col){
        if(matrix[currentRow + 1][currentCol] <= matrix[currentRow][currentCol] && matrix[currentRow + 1][currentCol] <= matrix[currentRow][currentCol + 1]){
            swap(matrix[currentRow][currentCol], matrix[currentRow + 1][currentCol]);
            maintainExtract(matrix, currentRow + 1, currentCol);
        }
        else if(matrix[currentRow][currentCol + 1] <= matrix[currentRow][currentCol] && matrix[currentRow][currentCol + 1] <= matrix[currentRow + 1][currentCol]){
            swap(matrix[currentRow][currentCol], matrix[currentRow][currentCol + 1]);
            maintainExtract(matrix, currentRow, currentCol + 1);
        }
        else{
            return;
        }
    }
    else if(currentRow + 1 < row){
        if(matrix[currentRow + 1][currentCol] <= matrix[currentRow][currentCol]){
            swap(matrix[currentRow][currentCol], matrix[currentRow + 1][currentCol]);
            maintainExtract(matrix, currentRow + 1, currentCol);
        }
        else{
            return;
        }
    }
    else if(currentCol + 1 < col){
        if(matrix[currentRow][currentCol + 1] <= matrix[currentRow][currentCol]){
            swap(matrix[currentRow][currentCol], matrix[currentRow][currentCol + 1]);
            maintainExtract(matrix, currentRow, currentCol + 1);
        }
        else{
            return;
        }
    }
    else{
        return;
    }
}

void insertYoung(vector<vector<long long>> &matrix, vector<long long> numlist, ofstream &fout){
    int row = matrix.size();
    int col = matrix[0].size();
    int i = row - 1;
    int j = col - 1;
    for(int k = 0; k < numlist.size(); k++){
        // printMatrix(matrix);
        if(matrix[i][j] == LONG_MAX){
            matrix[i][j] = numlist[k];
            // printMatrix(matrix);
            maintainInsert(matrix, i, j);
        }
        else{
            // fout << "Young Tableau is full" << endl;
        }
    }
}

int main(){
    ifstream fin("input.txt");
    int testCases;
    fin >> testCases;
    // cout << testCases << endl;
    ofstream fout("output.txt");
    for(int i = 0; i < testCases; i++){
        int instCode;
        fin >> instCode;
        // cout << instCode << endl;
        if(instCode == 1){
            fout << "Insert ";
            string insertNum;
            vector<long long> numList;
            vector<vector<long long>> matrix;
            fin.ignore();
            getline(fin, insertNum);

            stringstream ss(insertNum);
            string curentNum;
            while (ss >> curentNum){
                numList.push_back((long long)(stoi(curentNum)));
                // cout << curentNum << " ";
            }
            // cout << endl;
            for(int i = 0; i < numList.size(); i++){
                fout << numList[i];
                if(i != numList.size() - 1){
                    fout << " ";
                }
            }
            fout << endl;

            string line;
            while(getline(fin, line)){
                if(line.empty()){
                    break;
                }

                stringstream ss(line);
                vector<long long> row;
                string currentNum;
                while(ss >> currentNum){
                    if(currentNum == "x"){
                        row.push_back(LONG_MAX);
                        continue;
                    }
                    else{
                        row.push_back((long long)(stoi(currentNum)));
                    }
                }
                matrix.push_back(row);
            }

            insertYoung(matrix, numList, fout);

            for(int i = 0; i < matrix.size(); i++){
                for(int j = 0; j < matrix[0].size(); j++){
                    if(matrix[i][j] == LONG_MAX){
                        fout << "x ";
                    }
                    else{
                        fout << matrix[i][j] << " ";
                    }
                }
                fout << endl;
            }
            if(i != testCases - 1){
                fout << endl;
            }
        }
        else if(instCode == 2){
            fin.ignore();       
            fout << "Extract-min ";
            vector<vector<long long>> matrix;
            string line;
            while(getline(fin, line)){
                if(line.empty()){
                    break;
                }

                stringstream ss(line);
                vector<long long> row;
                string currentNum;
                while(ss >> currentNum){
                    if(currentNum == "x"){
                        row.push_back(LONG_MAX);
                        continue;
                    }
                    else{
                        row.push_back((long long)(stoi(currentNum)));
                    }
                }
                matrix.push_back(row);
            }
            
            fout << matrix[0][0] << endl;
            matrix[0][0] = LONG_MAX;
            maintainExtract(matrix, 0, 0);

            for(int i = 0; i < matrix.size(); i++){
                for(int j = 0; j < matrix[0].size(); j++){
                    if(matrix[i][j] == LONG_MAX){
                        fout << "x ";
                    }
                    else{
                        fout << matrix[i][j] << " ";
                    }
                }
                fout << endl;
            }
            if(i != testCases - 1){
                fout << endl;
            }
        }

    }
    fin.close();
    fout.close();
}