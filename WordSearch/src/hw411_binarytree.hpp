//
//  GVBinaryTree.hpp

#ifndef CS263_BinaryTree
#define CS263_BinaryTree
#include <stdexcept>
#include <ostream>
using namespace std;
namespace gvsu {
    template<typename Z>
    class BinaryTree {
    private:
        class Node;
        /* instance variables */
        Node *root;   /* pointer to the root node */
        /* inner class(es) */
        class Node {
        public:
            Z data;
            Node *left;   /* pointer to the left child */
            Node *right;  /* pointer to the right child */
        };
    public:
        /* member functions */

        BinaryTree () {
            root = nullptr;
        }

        ~BinaryTree() {
            if (root == nullptr)
                return;
            clearAll(root);
        }

        int numberOfNodes() const {
            FAIL ("I have to complete Question 4.31(a) by writing a private helper recursive function");
            /* in your recursive private function, make sure to avoid duplicate recursive calls */
            return 0;
        }

        /* Definition: a leaf node has no children */
        int numberOfLeaves() const {
            FAIL ("I have to complete Question 4.31(b) by writing a private helper recursive function");
            /* in your recursive private function, make sure to avoid duplicate recursive calls */
            return 0;
        }

        /* Definition:  a full node has two children */
        int numberOfFullNodes() const {
            FAIL ("I have to complete Question 4.31(c) by writing a private helper recursive function");
            /* in your recursive private function, make sure to avoid duplicate recursive calls */
            return 0;
        }

        /* copy assignment */
        BinaryTree&  operator= (const BinaryTree& rhs) {
            clearAll(root); /* required to avoid mem leak */
            root = duplicate (rhs.root);
            return *this;
        }

        /* move assignment */
        BinaryTree& operator= (BinaryTree&& rhs)
        {
            clearAll(root);
            this->root = rhs.root;
            rhs.root = nullptr;
            return *this;
        }

        bool contains (const Z& key) const
        {
            return is_element_of (root, key);
        }

        bool insert (const Z& key) {
            return insert_into (root, key);
        }

        void remove (const Z& key) {
            remove_from(root, key);
        }

        vector<Z> levelOrder () const {
            vector<Z> output;
            /* The returned string must be separated by commas */
            FAIL ("I have to complete Question 4.40 by invoking a private function");
            return output;
        }

        /* Use the following print for debugging. To call this function,
         * use one of the following invocations from your "main" function:
           (fill in the blank with the name of you tree object)

            ______.print();
            ______.print(std::cout);
            ______.print(your_own_output_stream);
         
            The last example can be used, for instance, to save the output
            to a file (by first creating an ofstream object)

         */
        void print (ostream& os = std::cout) const {
            print_from (root, os, "");
        }

    private:

        /* TODO: add as many as private functions as you wish */
        Node * duplicate_from (Node *theOtherNode)
        {
            FAIL("I have to complete duplicate");
            return nullptr;
        }

        bool is_element_of (Node *pos, const Z& key) const {
            FAIL("I have to complete this recursive function");
            return false;
        }
        
        bool insert_into (Node*& pos, const Z& key) const {
            FAIL("I have to complete this recursive function");
            return false;
        }
        
        void remove_from (Node*& pos, const Z& key) const {
            FAIL("I have to complete this recursive function");
        }
        
        void clearAll (Node* & pos) // remove all the nodes from this tree
        {
            FAIL("I have to complete clearAll");
        }

        void print_from (Node *pos, ostream& os, const string&& path) const
        {
            if (pos) {
                print_from (pos->left, os, path + "L");
                os << pos->data << " (" << path << ")" << endl;
                print_from (pos->right, os, path + "R");
            }
        }
    };

    template <typename Z>
    ostream& operator<< (ostream& os, const BinaryTree<Z>& t)
    {
        t.print (os);
        return os;
    }

}


#endif
