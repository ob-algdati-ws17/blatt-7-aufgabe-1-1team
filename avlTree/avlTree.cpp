#include "avlTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdio>

using namespace std;

//Tree Destructor
avlTree::~avlTree() {
    delete root;
}

//Node Destructor
avlTree::Node::~Node() {
    delete left;
    delete right;
}

bool avlTree::Node::hasChild() const {
    return left != nullptr || right != nullptr;
}

// Finde den kleinsten Key
avlTree::Node *avlTree::getSymmetricFollower(Node *node) {
    auto current = node->left;
    if(current != nullptr) {
        while(current->right != nullptr) {
            current = current->right;
        }
    }
    return current;
}

//Balancing Method
void avlTree::upIn(Node *start) {
    if (start != nullptr && start->parent != nullptr) {
        // Abbruch wenn bei Wurzel angekommen
        if (start == root) {
            return;
        } else {
            // Test ob Links eingefügt wird
            if (start->key < start->parent->key) {
                // Fall 1.1 bal P* = 1
                if (start->parent->balance = 1){
                    start->parent->balance = 0;
                    // Fall 1.2 bal P* = 0
                } else if (start->parent->balance = 0) {
                    start->parent->balance = -1;
                    upIn(start->parent);
                    // Fall 1.3.1 bal P* = -1 und eingefügt Links-Links
                } else if (start->parent->balance = -1){
                    rotateRight(start->parent);
                    // Fall 1.3.2 bal P* = -1 und eingefügt Links-Rechts
                } else {
                    Node *parent = start->parent;
                    rotateLeft(start);
                    rotateRight(parent);
                }
                // Test ob Rechts eingefügt wird
            } else if (start->key > start->parent->key) {
                // Fall 1.1 bal P* = -1
                if (start->parent->balance = -1) {
                    start->parent->balance = 0;
                    // Fall 1.2 bal P* = 0
                } else if (start->parent->balance = 0) {
                    start->parent->balance = 1;
                    upIn(start->parent);
                    // Fall 1.3.1 P* = 1 und eingefügt Rechts-Rechts
                } else if (start->balance = 1) {
                    rotateLeft(start->parent);
                    // Fall 1.3.2 P* = 1 und eingefügt Rechts-Links
                } else {
                    Node *parent = start->parent;
                    rotateRight(start);
                    rotateLeft(parent);
                }
            }
        }
    }

}

void avlTree::upOut(Node* start){
    //Linke Seite
    if (start != nullptr && start->parent) {
        // linker Nachfolger
        if (start->parent->left == start) {
            // Fall 1.1 bal P* = -1
            if (start->parent->balance == -1) {
                start->parent->balance = 0;
                upOut(start->parent);
            }
                // Fall 1.2 bal P* = 0
            else if (start->parent->balance == 0) {
                start->parent->balance = 1;
                // fertig
                // Fall 1.3
            } else {
                // Fall 1.3.1
                if (start->parent->right->balance == 0) {
                    rotateLeft(start->parent);
                    // Fall 1.3.2
                } else if (start->parent->right->balance == 1) {
                    Node* myR = start->parent->right;
                    rotateLeft(start->parent);
                    upOut(myR);
                    // Fall 1.3.3
                } else {
                    Node* myR = start->parent->right->left;
                    rotateRight(start->parent->right);
                    rotateLeft(start->parent);
                    upOut(myR);
                }

            }
            // Rechter Nachfolger
        } else {
            // Fall 2.1
            if (start->parent->balance == -1) {
                start->parent->balance = 0;
                upOut(start->parent);
            }
                // Fall 2.2
            else if (start->parent->balance == 0) {
                start->parent->balance = 1;
                // fertig
            }
                // Fall 2.3
            else {
                // Fall 2.3.1
                if (start->parent->left->balance == 0) {
                    rotateRight(start->parent);
                }
                    // Fall 2.3.2
                else if (start->parent->right->balance == 1){
                    Node* myR = start->parent->left->right;
                    rotateRight(start->parent);
                    upOut(myR);
                }
                    // Fall 2.3.3
                else {
                    Node* myR = start->parent->left->right;
                    rotateLeft(start->parent->right);
                    rotateRight(start->parent);
                    upOut(myR);
                }
            }
        }
    }
}

// rotate Methoden

//------Rotate Linksherum------//
void avlTree::rotateLeft(Node* node) {
    Node *rightside = node->right;
    Node *saveParent = node->parent;
    Node *t2 = node->right->left;
    if (saveParent == nullptr) {
        root = rightside;
        root->left = node;
        node->left = t2;
    } else {
        // Rotiere Links Herum
        saveParent->right = rightside;
        saveParent->balance -= 1;
        rightside->right = node;
        rightside->balance -= 1;
        node->right = t2;
    }
}

//------Rotate Rechtsherum-------//
void avlTree::rotateRight(Node* node) {
    Node* leftside = node->left;
    Node* saveParent = node->parent;
    Node* t2 = node->left->right;
    if (saveParent == nullptr) {
        root = leftside;
        root->right = node;
        node->right = t2;
    } else {
        // Rotiere Rechts herum
        saveParent->left = leftside;
        saveParent->balance += 1;
        leftside->right = node;
        leftside->balance +=1;
        node->left = t2;
    }
}

//-----Bestimme Höhe für Remove------//
int avlTree::getHeight(Node* p) {
    return max(p->left == nullptr ? 0 : getHeight(p->left) + 1, p->right == nullptr ? 0 : getHeight(p->right) + 1);
}

//-----Einfügen von Neuen Knoten mit value----//
void avlTree::insert(const int value) {
    // Prüfe nach ob key schon existiert
    if (search(value)) {
        return;
        // Prüfe ob nach der Wurzel direkt eingefügt werden kann
    } else if(root==nullptr) {
        root = new Node(value, nullptr);
    } else {
        Node *current = root;
        // Suche Platz für den Knoten
        while (true) {
            // Flag ob Rechts/Links eingefügt wird
            bool isRight = current->key < value;
            if (isRight) {
                // Teste ob "freier Platz" bzw. Unterste Knotenschicht
                if(current->right == nullptr) {
                    current->right = new Node(value,current);
                    upIn(current->left);
                    break;
                } else {
                    // Gehe Schicht tiefer
                    current = current->right;
                }
            } else {
                // Teste ob "freier Platz" bzw. Unterste Knotenschicht
                if(current->left == nullptr) {
                    current->left = new Node(value, current);
                    upIn(current->left);
                    break;
                } else {
                    // Gehe Schicht tiefer
                    current = current->left;
                }
            }
        }
    }
}

//-------Search Methode ruft mit Root Rekursive Search auf----
bool avlTree::search(const int value) const {
    search(value,root);
}
//------Rekursive Search Methode-------
bool avlTree::search(const int value, Node *node) const {
    // Wenn am Ende angekommen wird false hoch gegeben
    if (node == nullptr) {
        return false;
        // Wenn value mit dem Knoten Key übereinstimmt return True
    } else if (node->key == value) {
        return true;
        // Vergleiche Wert mit value
        // Kleiner als value-->Fortfahren mit Linkem Knoten
        // Größer als value-->Fortfahren mit Rechtem Knoten
    } else if (value < node->key) {
        return search(value,node->left);
    } else if ( value > node->key) {
        return search(value,node->right);
    }
}



//------Remove Methode----//
// Prüfe gleich am Anfang ob der Wert existiert, ansonsten rekursiver Remove Aufruf mit Wurzel
void avlTree::remove(const int value) {
    if (!search(value)) {
        return;
    } else {
        remove(value,root);
    }
}
//-----Rekursive Remove Methode------//
void avlTree::remove(const int value, Node *node) {




    // Lösche einzigen Knoten: die Wurzel
    if (node == root  ) {
        if (!node->hasChild()) {
            delete node;
            root = nullptr;
            return;
        } else {
            // Entferne Wurzel
            Node* leftSide = node;
        }
    }
    Node* parent1 = node->parent;
    int q = 0;
    // Fall 1
    if (node->key == value) {
        if (!node->hasChild()) {
            if(node == root) {
                root = nullptr;
                free(node);
                return;
            }
            // Linke Seite wird Removed
            if (node == node->parent->left) {
                node->parent->left = nullptr;
                q = getHeight(node->parent);
                // Fall 1 mit Höhe von q(Teilbaum) 1
                if (q == 1) {
                    node->parent->balance = 1;
                    // Fall 1 mit Höhe von q = 0
                } else if (q == 0) {
                    upOut(node->parent);
                    // Fall 1 mit Höhe von q = 0
                } else {
                    if (node->parent->right->left != nullptr) {
                        rotateRight(node->parent->right);
                        rotateLeft(node->parent);
                    } else {
                        rotateLeft(node->parent);
                    }
                    upOut(node->parent);
                }
                // Rechte Seite äquivalent zu Unterschiedlichen Höhen bei Fall 1
            } else {
                node->parent->right = nullptr;
                q = getHeight(node->parent);
                if (q == 1) {
                    node->parent->balance = 1;
                } else if (q == 0) {
                    upOut(node->parent);
                } else {
                    if (node->parent->left->right != nullptr) {
                        rotateLeft(node->parent->left);
                        rotateRight(node->parent);
                    } else {
                        rotateRight(node->parent);
                    }
                    upOut(node->parent);
                }
            }
            upOut(node->parent);

            // Fall 2 1 Knoten 1 Leaf
        } else if (node->left || node->right == nullptr) {
            if (node == root) {
                root = root->left == nullptr ? root->right : root->left;
                root->parent = nullptr;
                return;
            }
            if (node->parent->left == node) {
                // Links kein Blatt
                if (node->left == nullptr) {
                    parent1->left = node->right;
                    parent1->balance += 1;
                    parent1->left->right = nullptr;
                } else {
                    parent1->left = node->left;
                    parent1->balance -= 1;
                    parent1->left->left = nullptr;
                }
                node->parent->left->parent = node->parent;
            } else {
                // Rechts kein Blatt
                if (node->left == nullptr) {
                    parent1->right = node->right;
                    parent1->balance += 1;
                    parent1->right->right = nullptr;
                } else {
                    parent1->right = node->left;
                    parent1->balance -= 1;
                    parent1->right->left = nullptr;
                }
                node->parent->right->parent = node->parent;
            }

            upOut(node->parent);

            // Fall 3 Beide Nachfolger Knoten
            // Symmetrischer Nachfolger
            Node *symmetric = getSymmetricFollower(node);
            node->key = symmetric->key;
            remove(value, symmetric);
        }
    } else {
        // Hangel dich tiefer durch den Baum bis Links fertig geprüft wurde, dann weiter mit Rechtem Teilbaum
        if (node->left != nullptr) {
            remove(value, node->left);
        }
        if (node->right != nullptr) {
            remove(value, node->right);
        }
    }

}

//-----Gib den Baum inOrder an
std::vector<int> *avlTree::inorder() const {
    // Brich ab wenn Leerer Baum
    if (root == nullptr) {
        return nullptr;
    } else {
        auto* tree = new std::vector<int>();
        // Rekursiver Aufruf
        inorder(root,tree);
        /* for(auto i = tree->begin(); i != tree->end(); i++)
             {
                 std::cout<<*i<<endl;
             } */
        return tree;
    }
}

std::vector<int> *avlTree::inorder(Node *node, std::vector<int> *tree) const {
    // Linke seite
    if (node->left != nullptr) {
        // Gehe zum Ende des linken Teilbaums
        inorder(node->left, tree);
    }
    // Füge niedrigsten Key in Vektor ein
    tree->push_back(node->key);
    // Rechte Seite zum Ende des Teilbaums
    if (node->right != nullptr) {
        inorder(node->right,tree);
    }
    return tree;
}
