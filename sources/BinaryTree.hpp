#pragma once
#include <iostream>
#include <stack>
#include<vector>
namespace ariel{
    template <class Type>
    class BinaryTree{
        public:
            class Node{
            public:
                Node * father;
                Node * left;
                Node * right;
                Type value;

                Node(Type val):value(val),father(nullptr),left(nullptr),right(nullptr){}
                
                // Node(Node * other):left(nullptr),right(nullptr),value(other->value){
                //     if (other->left != nullptr ){
                //         left = new Node(*other->left);
                //     }
                //     if (other->right != nullptr){
                //         right = new Node(*other->right);
                //     }
                // }
            };
        Node * head;
        BinaryTree():head(nullptr){}
        ~BinaryTree(){
            
        }
        BinaryTree(BinaryTree&& other)noexcept{
            this->head = other.head;
            other.head=nullptr;
        }
        BinaryTree(const BinaryTree& other){
            this->head = other.head;
        }
        BinaryTree& operator=(BinaryTree&& other) noexcept{
            if(head){
                delete head;
            }
            this->head = other.head;
            other.head = nullptr;
            return *this;
        }

        BinaryTree& operator=(BinaryTree const& other){
            if(this ==&other){
                return *this;
            }
            if(head){
                delete head; 
            }
            if(other.head){
            // delete head;
            // this->head = new Node(other.head->value);
            head = &(biuld(this->head,other.head));
            // delete other.head;
            }
            return *this;
        }
        Node& biuld(Node * root,Node * other){
            if(!other){
                return *root;
            }
            root=new Node(other->value);
            root->left = &(biuld(root->left,other->left));
            root->right = &(biuld(root->right,other->right));
            return *root;
        }

        BinaryTree& add_root(const Type a){
            if(this->head){
                head->value = a;
            }
            else{
                head = (Node*)new Node(a);
            }
            return *this;
        }
        BinaryTree& add_left(const Type a,const Type b){
            Node * temp = search(head,a);
            if(temp==nullptr){
                throw(std::invalid_argument{"no matching node from the left"});           
            }
            if(!temp->left){
                temp->left = (Node *)new Node(b);
            }
            else{
                temp->left->value = b;
            }
            return *this;
        }

        BinaryTree& add_right(const Type &a,const Type &b){
            Node * temp = search(head,a);
            if(temp==nullptr){
                throw(std::invalid_argument{"no matching node from the right"});           
            }
            if(!temp->right){
                temp->right = (Node *)new Node(b);
            }
            else{
                temp->right->value = b;
            }
            return *this;
        }

    Node* search(Node* node, Type name){
        if(node != nullptr){
            if(node->value==name){
                return node;
            } 
            Node * foundNode = search( node->left,name);
            if(foundNode == nullptr) {
                foundNode = search(node->right,name);
            }
            return foundNode;
        } 
        return nullptr;

    }

    friend std::ostream& operator<< (std::ostream& output, BinaryTree& c){
        c.printInorder(c.head);
        std::cout<<std::endl;
        return output;
    }
    void printInorder(Node* node){
        if (node == NULL){
            return;
        }
        printInorder(node->left);
        std::cout << node->value << " ";
        printInorder(node->right);
    }

    class inorder_iterator {
        public:
        Node * root;
        Node * pointer;
        std::vector<Node *> stack;
        inorder_iterator(Node * ptr=nullptr):root(ptr),pointer(ptr){
            biuld(root); 
            if(stack.size()>1){
                root = stack[0];
            }
        }
        void biuld(Node * h){
            if(!h){
                return;
            }
            biuld(h->left);
            stack.push_back(h);
            biuld(h->right);
            
        }
        Type& operator*(){
            return this->root->value;
        }
        Type* operator->(){
            return &(this->root->value);
        }
        inorder_iterator& operator++(){
            if(stack.size()>1){
                stack.erase(stack.begin());
                root = stack[0];
            }
            else{
            root = nullptr;
            }
            return *this;
        }
        inorder_iterator operator++(int){
            inorder_iterator temp = *this;
            if(stack.size()>1){
                stack.erase(stack.begin());
                root = stack[0];
            }
            else{
            root = nullptr;
            } 
            return temp;
        }
        bool operator==(const inorder_iterator &itr){

            return this->root==itr.root;
        }
        bool operator!=(const inorder_iterator &itr){
            return this->root!=itr.root;
        }
    };
    class preorder_iterator {
        // private:
        public:
        Node * root;
        std::vector<Node *> stack;
        preorder_iterator(Node* ptr=nullptr):root(ptr){
            biuld(root); 
            if(stack.size()>1){
                root = stack[0];
            }
        }
        void biuld(Node * h){
            if(!h){
                return;
            }
            stack.push_back(h);
            biuld(h->left);
            biuld(h->right);
        }
        Type& operator*(){
            return this->root->value;
        }
        Type* operator->(){
            return &(this->root->value);
        }
        preorder_iterator& operator++(){
            if(stack.size()>1){
                stack.erase(stack.begin());
                root = stack[0];
            }
            else{
            root = nullptr;
            }
            return *this;
        }
        preorder_iterator operator++(int){
            preorder_iterator temp = *this;
            if(stack.size()>1){
                stack.erase(stack.begin());
                root = stack[0];
            }
            else{
            root = nullptr;
            } 
            return temp;
        }
        bool operator==(const preorder_iterator &itr){
            return this->root==itr.root;
        }
        bool operator!=(const preorder_iterator &itr){
            return this->root!=itr.root;
        }
    };
    class postorder_iterator {
        // private:
        public:
        Node * root;
        std::vector<Node *> stack;
        postorder_iterator(Node* ptr=nullptr):root(ptr){
            biuld(root); 
            if(stack.size()>1){
                root = stack[0];
            }
        }
        void biuld(Node * h){
            if(!h){
                return;
            }
            biuld(h->left);
            biuld(h->right);
            stack.push_back(h);
        }
        Type& operator*(){
            return this->root->value;
        }
        Type* operator->(){
            return &(this->root->value);
        }
        postorder_iterator& operator++(){
            if(stack.size()>1){
                stack.erase(stack.begin());
                root = stack[0];
            }
            else{
            root = nullptr;
            }
            return *this;
        }
        postorder_iterator operator++(int){
            postorder_iterator temp = *this;
            if(stack.size()>1){
                stack.erase(stack.begin());
                root = stack[0];
            }
            else{
            root = nullptr;
            } 
            return temp;
        }
        bool operator==(const postorder_iterator &itr){
            return this->root==itr.root;
        }
        bool operator!=(const postorder_iterator &itr){
            return this->root!=itr.root;
        }
    };
        inorder_iterator begin(){
            return inorder_iterator{head};
        }
        preorder_iterator begin_preorder(){
            return preorder_iterator{head};
        }
        inorder_iterator begin_inorder(){
            return inorder_iterator{head};
        }
        postorder_iterator begin_postorder(){
            return postorder_iterator{head};
        }
        inorder_iterator end(){
            return inorder_iterator{nullptr};
        }
        inorder_iterator end_inorder(){
            return inorder_iterator{nullptr};
        }
        
        preorder_iterator end_preorder(){
            return preorder_iterator{nullptr};
        }
        postorder_iterator end_postorder(){
            return postorder_iterator{nullptr};
        }
};
}


 
