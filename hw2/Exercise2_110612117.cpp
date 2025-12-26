#include <iostream>
#include <vector>
#include <list>
#include <fstream>
using namespace std;
bool testMode = false;
class Node{
    public:
        int data;
        Node* left;
        Node* right;
        Node* parent;
        bool color; // 0: Black, 1: Red
        Node(int data){
            this->data = data;
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
            this->color = 1;
        }
};

Node* leftRotation(Node* root, Node* node){
    // cout << "left rotation" << endl;
    Node* right = node->right;
    node->right = right->left;
    if(right->left != NULL){
        right->left->parent = node;
    }
    right->parent = node->parent;
    if(node->parent == NULL){
        root = right;
    }
    else if(node == node->parent->left){
        node->parent->left = right;
    }
    else{
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
    return root;
}

Node* rightRotation(Node* root, Node* node){
    // cout << "right rotation" << endl;
    Node* left = node->left;
    node->left = left->right;
    if(left->right != NULL){
        left->right->parent = node;
    }
    left->parent = node->parent;
    if(node->parent == NULL){
        root = left;
    }
    else if(node == node->parent->right){
        node->parent->right = left;
    }
    else{
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
    return root;
}

Node* traverseRBTree(Node* root, int node){
    // cout << "traverse " << node << endl;
    Node* cur = root;
    while(cur != NULL){
        if(node < cur->data){
            if(cur->left == NULL){
                return cur;
            }
            cur = cur->left;
        }
        else if(node > cur->data){
            if(cur->right == NULL){
                return cur;
            }
            cur = cur->right;
        }
        else{
            return cur;
        }
    }
}

Node* insertRBTree(Node* root, int node){
    // cout << "insert " << node << endl;
    Node* newNode = new Node(node);
    if(root == NULL){
        root = newNode;
        root->color = 0;
        if(testMode){
            cout << "root: " << root->data << endl;
        }
        return root;
    }

    Node* cur = traverseRBTree(root, node);
    if(testMode){
        cout << "cur: " << cur->data << endl;
    } 
    if(cur->data == node){
        return root;
    }

    newNode->parent = cur;
    if(testMode){
        cout << "new: " << newNode->data << endl;
        cout << "new parent: " << newNode->parent->data << endl;
    }

    if(node < cur->data){
        cur->left = newNode;
        if(testMode){
            cout << "left: " << cur->left->data << endl;
        }
    }
    else{
        cur->right = newNode;
        if(testMode){
            cout << "right: " << cur->right->data << endl;
        }
    }

    while(newNode != root && newNode->parent->color == 1){
        if(newNode->parent == newNode->parent->parent->left){
            Node* uncle = newNode->parent->parent->right;
            if(uncle != NULL && uncle->color ==1){
                newNode->parent->color = 0;
                uncle->color = 0;
                if(newNode->parent->parent != root){
                    newNode->parent->parent->color = 1;
                }
                newNode = newNode->parent->parent;
            }
            else{
                if(newNode == newNode->parent->right){       // left-right
                    newNode = newNode->parent;
                    root = leftRotation(root, newNode);
                }
                newNode->parent->color = 0;                 // left-left
                newNode->parent->parent->color = 1;
                root = rightRotation(root, newNode->parent->parent);
            }

        }
        else{
            Node* uncle = newNode->parent->parent->left;
            if(uncle != NULL && uncle->color == 1){
                newNode->parent->color = 0;
                uncle->color = 0;
                if(newNode->parent->parent != root){
                    newNode->parent->parent->color = 1;
                }
                newNode = newNode->parent->parent;
            }
            else{
                if(newNode == newNode->parent->left){       // right-left
                    newNode = newNode->parent;
                    root = rightRotation(root, newNode);
                }
                newNode->parent->color = 0;                 // right-right
                newNode->parent->parent->color = 1;
                root = leftRotation(root, newNode->parent->parent);
            }
        }
    }
    if(testMode){
        cout << "insert end" << endl;
    }
    return root;
}

Node* findSuccessor(Node* node){
    Node* cur = node->right;
    if(cur == NULL){
        return node;
    }
    while(cur->left != NULL){
        cur = cur->left;
    }
    return cur;
}

Node* deleteRBTree(Node* root, int node){
    // cout << "delete " << node << endl;
    Node* cur = traverseRBTree(root, node);
    if(cur == NULL || cur->data != node){
        cout << "Node " << node << " is not in the tree." << endl;
        return root;
    }
    // cout << "find " << node << endl;
    if(testMode){
        cout << "cur: " << cur->data << endl;
    }
    Node* del = cur;
    Node* successor = findSuccessor(del);
    if(testMode){
        cout << "del: " << del->data << endl;
        cout << "successor: " << successor->data << endl;
    }

    del->data = successor->data;
    if(successor == root){
        if(successor->left != NULL){
            root = successor->left;
            root->parent = NULL;
            root->color = 0;
            return root;
        }
        else if(successor->right != NULL){
            cout << "successor should not have right child..." << endl;
            root = successor->right;
            root->parent = NULL;
            return root;
        }
        else{
            delete successor;
            return NULL;
        }
    }

    if(successor->color == 1){
        if(testMode){
            cout << "successor is red" << endl;
        }
        if(successor->left == NULL && successor->right == NULL){
            if(successor->parent->left == successor){
                successor->parent->left = NULL;
            }
            else{
                successor->parent->right = NULL;
            }
            delete successor;
            return root;
        }
    }
    else if(successor->color == 0){
        if(testMode){
            cout << "successor is black" << endl;
        }
        if(successor->right != NULL && successor->right->color == 1){
            if(testMode){
                cout << "successor has red right child" << endl;
            }
            if(successor->parent->left == successor){
                successor->parent->left = successor->right;
                successor->right->parent = successor->parent;
                successor->right->color = 0;
                delete successor;
                return root;
            }
            else if(successor->parent->right == successor){
                successor->parent->right = successor->right;
                successor->right->parent = successor->parent;
                successor->right->color = 0;
                delete successor;
                return root;
            }
        }
        else if(successor->left != NULL && successor->left->color == 1){
            if(testMode){
                cout << "successor has red left child" << endl;
            }
            if(successor->parent->left == successor){
                successor->parent->left = successor->left;
                successor->left->parent = successor->parent;
                successor->left->color = 0;
                delete successor;
                return root;
            }
            else if(successor->parent->right == successor){
                successor->parent->right = successor->left;
                successor->left->parent = successor->parent;
                successor->left->color = 0;
                delete successor;
                return root;
            }
        }
        else{
            if(testMode){
                cout << "successor is black and has no red child" << endl;
            }
            int successorIsLeft = successor->parent->left == successor ? 1 : 0;
            if(successor->parent->left == successor){
                successor->parent->left = NULL;
            }
            else{
                successor->parent->right = NULL;
            }
            int count = 1;
            while(true){
                // if(count != 1 && successor->parent != NULL){
                //     successorIsLeft = successor->parent->left == successor ? 1 : 0;
                // }
                // count--;
                if(successor->parent == NULL){                            //case 1
                    if(testMode){
                        cout << "case 1" << endl;
                    }
                    root = successor;
                    return root;
                }
                else if(successorIsLeft == 1){
                    if(testMode){
                        cout << "successor is left child" << endl;
                    }
                    Node *sibling = successor->parent->right;
                    if(successor->parent->color == 0){
                        if(sibling->color == 1){                          //case 2
                            if(testMode){
                                cout << "case 2" << endl;
                            }
                            successor->parent->color = 1;
                            sibling->color = 0;
                            root = leftRotation(root, successor->parent);
                            sibling = successor->parent->right;
                        }
                        else if(sibling->color == 0){
                            int leftColor = sibling->left == NULL ? 0 : sibling->left->color;
                            int rightColor = sibling->right == NULL ? 0 : sibling->right->color;
                            if(testMode){
                                cout << "leftColor: " << leftColor << ", rightColor: " << rightColor << endl;
                            }
                            if(leftColor == 0 && rightColor == 0){    //case 3
                                if(testMode){
                                    cout << "case 3" << endl;
                                }
                                sibling->color = 1;
                                successor = successor->parent;
                                if(successor->parent != NULL){
                                    successorIsLeft = successor->parent->left == successor ? 1 : 0;
                                }
                            }
                            else if(rightColor == 0){                //case 5
                                if(testMode){
                                    cout << "case 5" << endl;
                                }
                                if(sibling->left != NULL){
                                    sibling->left->color = 0;
                                }
                                sibling->color = 1;
                                root = rightRotation(root, sibling);
                                sibling = successor->parent->right;
                            }
                            else if(rightColor == 1){                //case 6
                                if(testMode){
                                    cout << "case 6" << endl;
                                }
                                sibling->color = successor->parent->color;
                                successor->parent->color = 0;
                                if(sibling->right != NULL){
                                    sibling->right->color = 0;
                                }
                                root = leftRotation(root, successor->parent);
                                return root;
                            }
                        }
                    }
                    else if(successor->parent->color == 1){
                        if(sibling->color == 1){
                            cout << "Something went wrong, Red-Red should not happen" << endl;
                        }
                        else if(sibling->color == 0){
                            int leftColor = sibling->left == NULL ? 0 : sibling->left->color;
                            int rightColor = sibling->right == NULL ? 0 : sibling->right->color;
                            if(leftColor == 0 && rightColor == 0){    //case 4
                                if(testMode){
                                    cout << "case 4" << endl;
                                }
                                sibling->color = 1;
                                successor->parent->color = 0;
                                return root;
                            }
                            else if(rightColor == 0){                //case 5
                                if(testMode){
                                    cout << "case 5" << endl;
                                }
                                if(sibling->left != NULL){
                                    sibling->left->color = 0;
                                }
                                sibling->color = 1;
                                root = rightRotation(root, sibling);
                                sibling = successor->parent->right;
                                if(testMode){
                                    cout << "siblings left: " << sibling->left->data << endl;
                                    cout << "siblings right: " << sibling->right->data << endl;
                                    cout << "sibling parent: " << sibling->parent->data << endl;
                                    cout << "successor: " << successor->data << endl;
                                    cout << "parent: " << successor->parent->data << endl;
                                }
                            }
                            else if(rightColor == 1){                //case 6
                                if(testMode){
                                    cout << "case 6" << endl;
                                }
                                sibling->color = successor->parent->color;
                                successor->parent->color = 0;
                                if(sibling->right != NULL){
                                    sibling->right->color = 0;
                                }

                                root = leftRotation(root, successor->parent);
                                return root;
                            }
                        }
                    }
                }
                else if(!successorIsLeft){
                    if(testMode){
                        cout << "successor is right child" << endl;
                    }
                    Node *sibling = successor->parent->left;
                    if(successor->parent->color == 0){
                        if(sibling->color == 1){                          //case 2
                            if(testMode){
                                cout << "case 2" << endl;
                            }
                            successor->parent->color = 1;
                            sibling->color = 0;
                            root = rightRotation(root, successor->parent);
                            sibling = successor->parent->left;
                        }
                        else if(sibling->color == 0){
                            int leftColor = sibling->left == NULL ? 0 : sibling->left->color;
                            int rightColor = sibling->right == NULL ? 0 : sibling->right->color;
                            if(leftColor == 0 && rightColor == 0){    //case 3
                                if(testMode){
                                    cout << "case 3" << endl;
                                }
                                sibling->color = 1;
                                successor = successor->parent;
                                if(successor->parent != NULL){
                                    successorIsLeft = successor->parent->left == successor ? 1 : 0;
                                }
                                if(testMode){
                                    cout << "successor: " << successor->data << endl;
                                }
                            }
                            else if(leftColor == 0){                //case 5
                                if(testMode){
                                    cout << "case 5" << endl;
                                }
                                if(sibling->right != NULL){
                                    sibling->right->color = 0;
                                }
                                sibling->color = 1;
                                root = leftRotation(root, sibling);
                                sibling = successor->parent->left;
                            }
                            else if(leftColor == 1){                //case 6
                                if(testMode){
                                    cout << "case 6" << endl;
                                }
                                sibling->color = successor->parent->color;
                                successor->parent->color = 0;
                                if(sibling->left != NULL){
                                    sibling->left->color = 0;
                                }
                                root = rightRotation(root, successor->parent);
                                return root;
                            }
                        }
                    }
                    else if(successor->parent->color == 1){
                        if(sibling->color == 1){
                            cout << "Something went wrong, Red-Red should not happen" << endl;
                        }
                        else if(sibling->color == 0){
                            int leftColor = sibling->left == NULL ? 0 : sibling->left->color;
                            int rightColor = sibling->right == NULL ? 0 : sibling->right->color;
                            if(leftColor == 0 && rightColor == 0){    //case 4
                                if(testMode){
                                    cout << "case 4" << endl;
                                }
                                sibling->color = 1;
                                successor->parent->color = 0;
                                return root;
                            }
                            else if(leftColor == 0){                //case 5
                                if(testMode){
                                    cout << "case 5" << endl;
                                }
                                if(sibling->right != NULL){
                                    sibling->right->color = 0;
                                }
                                sibling->color = 1;
                                root = leftRotation(root, sibling);
                                sibling = successor->parent->left;
                            }
                            else if(leftColor == 1){                //case 6
                                if(testMode){
                                    cout << "case 6" << endl;
                                }
                                sibling->color = successor->parent->color;
                                successor->parent->color = 0;
                                if(sibling->left != NULL){
                                    sibling->left->color = 0;
                                }
                                root = rightRotation(root, successor->parent);
                                return root;
                            }
                        }
                    }
                }
            }
        }
    }

    
}

void printRBTree(Node* root, ofstream& fout){
    // cout << "print" << endl;
    list<Node*> queue;
    queue.push_back(root);
    while(!queue.empty()){
        Node* cur = queue.front();
        if(testMode){
            cout << "cur: " << cur->data << endl;
        }
        string color = cur->color ? "Red" : "Black";
        string parent = cur->parent == NULL ? "nil" : to_string(cur->parent->data);
        string left = cur->left == NULL ? "nil" : to_string(cur->left->data);
        string right = cur->right == NULL ? "nil" : to_string(cur->right->data);
        fout << "Node: " << cur->data << ", Parent: " << parent << ", Left: " << left << ", Right: " << right << ", Color: " << color << endl;
        if(cur->left != NULL){
            queue.push_back(cur->left);
        }
        if(cur->right != NULL){
            queue.push_back(cur->right);
        }
        queue.pop_front();
    }

}

int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int op_num;
    fin >> op_num;
    Node* root = NULL;
    while(op_num--){
        int op, numOfNode;
        fin >> op >> numOfNode;
        if(op == 1){
            fout << "Insert:";
            while(numOfNode--){
                int node;
                fin >> node;

                fout << " " << node;
                if(numOfNode != 0){
                    fout << ",";
                }
                else{
                    fout << endl;
                }

                root = insertRBTree(root, node);
                if(testMode){
                    cout << "root: " << root->data << endl;
                }
            }
            printRBTree(root, fout);
            fout << endl;
        }
        else if(op == 2){
            fout << "Delete:";
            while(numOfNode--){
                int node;
                fin >> node;

                fout << " " << node;
                if(numOfNode != 0){
                    fout << ",";
                }
                else{
                    fout << endl;
                }

                root = deleteRBTree(root, node);
            }

            if(root != NULL){
                printRBTree(root, fout);   
            }
            else{
                fout << "Tree is empty." << endl;
            }
            fout << endl;
        }
    }
}