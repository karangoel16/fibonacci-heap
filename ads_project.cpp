//This code has been written by Karan Goel ,Student at University of Florida

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>

//All the header files have been added here

using namespace std;
//this is the basic node structure used
struct node {
    int val;// this will keep the frequencies
    int degree;//this will keep the number of children a node has
    string key;//this will keep the name of the node
    struct node *parent;//this will save the parent pointer
    bool child_cut;//this will keep track of the child cut if it is true or not
    struct node *link_child;//this will store the link list of the child pointer
    struct node *link_list_right;//this will store the the link of the next pointer
    struct node *link_list_left;//this will store the link of the previous node
}*head;

//making the map to be global so that it can be used within the functions as well

unordered_map<string, struct node *> umap;//this will be used to save the
std::map <int,struct node *>table;//this is used for pairwise combine


//Prototyping

//this code melds the two fibonacci heap into one
bool meld(struct node *root1,struct node *root2)
{
    struct node *temp1=root1->link_list_right;
    struct node *temp2=root2->link_list_left;
    root1->link_list_right=root2;
    root2->link_list_left=root1;
    temp1->link_list_left=temp2;
    temp2->link_list_right=temp1;
    return true;
}
//this function returns the vector of the nodes that are that same level
//in our code it is level 0 and it is used for pairwise combine later.
vector<struct node *> check(struct node *root)
{
    //here tell takes all the root nodes of max trees ,
    //also we are setting the pointer of head node in this code only
    vector <struct node *> tell;
    struct node *temp=root;
    do
    {
        tell.push_back(temp);
        if(head->val<temp->val)
        {
            head=temp;
        }
        temp=temp->link_list_left;
    }while(temp!=root);
    return tell;
}
//this function is used to add a new node in the heap if the head is initially empty we will add a new node and later
//we will add to the head node
struct node * add(string name,int freq)
{
    //if the head is null we are going a new node to the head and then making if a node , with left and right pointer
    //pointing to itself
    if(head==NULL)
    {
        head=new node();
        head->child_cut=false;
        head->val=freq;
        head->key=name;
        head->parent=NULL;
        head->link_child=NULL;
        head->link_list_right=head;
        head->link_list_left=head;
        head->degree=0;
        return head;
    }
    //otherwise we will need to make a new node and meld it to the head node , i.e. the fibonacci heap
    else
    {
        struct node *temp=new node();
        temp->val=freq;
        temp->key=name;
        temp->parent=NULL;
        temp->link_child=NULL;
        temp->child_cut=false;
        temp->degree=0;
        temp->link_list_left=temp;
        temp->link_list_right=temp;
        meld(head,temp);
        if(head->val<freq)
            head=temp;
        return temp;
    }
    return head;
};

//this is used for pairwise combine of the two node , it melds the smaller of the two as the root node and other as parent node.
//along with this it will check that if the child node is null it will add directly otherwise meld it to the node which is the
//child node of the bigger true , changing the value of the root node to be node
struct node * pairwise_comb(struct node *root1,struct node *root2)
{
    //we will interchange the node if the root2 is bigger than root 1
    if(root2->val>root1->val)
    {
        struct node *temp=root1;
        root1=root2;
        root2=temp;
    }
    //we will take out the root2 node (i.e. the smaller node (without changing the structure of the heap and then combine the two node
    root2->parent=root1;
    root2->link_list_right->link_list_left=root2->link_list_left;
    root2->link_list_left->link_list_right=root2->link_list_right;
    root1->degree=root1->degree+1;
    root2->child_cut=false;
    if(root1!=NULL && root1->link_child==NULL)
    {
        root1->link_child=root2;
        root2->link_list_left=root2;
        root2->link_list_right=root2;
        return root1;
    }
    if(root1!=NULL && root1->link_child!=NULL)
    {
        struct node *temp=root1->link_child;
        root2->link_list_left=root2;
        root2->link_list_right=root2;
        meld(temp,root2);
        return root1;
    }
    return NULL;
};
// this will keep on working till it finds a empty place in the map , where it can be entered
struct node * pairwise_vec(struct node *root)
{
    //we will keep looping the element till we are able to enter an element in the map
    int flag=1;
    while(flag)
    {
        std::map<int,struct node *>::iterator it;
        it=table.find(root->degree);
        if(it==table.end())
        {
            //here we will insert the element into hashmap and then return from the program
            table.insert(std::pair<int,struct node *>(root->degree,root));
            return root;
        }
        else if(root!=it->second)
        {
            struct node *p=it->second;
            table.erase(it);
            root=pairwise_comb(p,root);
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
}
//this code with the help of other funcationality such as check and pairwise combine
struct node * remove_max()
{
    //temp is to keep the value of the maximum in case needed later
    //temp2 is to create a new list
    if(head==NULL)
    {
        return head;
    }
    //if head is the only element in the heap
    if(head->link_child==NULL && head->link_list_left==head)
    {
        struct node *temp=head;
        head=NULL;
        return temp;//ts is done to remove the head from the node keeping the memory of the key intact and yet removing the array
    }
    //this is done to remove all the child of head and then meld it into head only
    if(head->degree!=0)
    {
        struct node *temp=head->link_child;
        head->degree=0;
        head->link_child=NULL;
        struct node *temp2=temp;
        do
        {

            temp->parent=NULL;
            temp=temp->link_list_left;
        }
        while(temp!=temp2);
        //we will meld the children of head with head itself
        meld(head,temp);
    }
    //this is to remove the head without changing the structure of the fibonacci heap
    struct node *value_saver = head;
    struct node *temp1=head->link_list_right;
    head->link_list_left->link_list_right=head->link_list_right;
    head->link_list_right->link_list_left=head->link_list_left;
    if(temp1->link_list_left==temp1)
    {
        head=temp1;
        return value_saver;
    }
    struct node *temp2=temp1;
    head=temp1;
    vector<struct node *> l=check(temp2);
    int i=0;
    table.clear();
    while(i<l.size())
    {
        temp1=pairwise_vec(l[i]);
        i++;
    }
    return value_saver;
}

//it is used to increase a particular key and then check if it greater than parent and perform child cut if necessary

int increasekey(struct node *root,int freq)
{
    //this is done to check if the root is not null
    if(root==NULL)
    {
        return -1;
    }
    //this is done to increase the element which is already a root node and then you don't need to go for child cut operation
    if(root->parent==NULL)
    {
        root->val=root->val+freq;
        if(root->val>head->val)
        {
            head=root;
        }
        return 1;
    }
    if(root->parent!=NULL)
    {
        root->val=root->val+freq;
        if(root->val<root->parent->val)
        {
            return 1;
        }
        else
        {
            if(root->parent->child_cut==false)
            {
                if(root->link_list_left==root)
                {
                    root->parent->link_child=NULL;
                }
                else
                {
                    root->parent->link_child=root->link_list_left;
                    root->link_list_left->link_list_right=root->link_list_right;
                    root->link_list_right->link_list_left=root->link_list_left;
                    root->link_list_left=root;
                    root->link_list_right=root;
                }
                root->parent->degree=root->parent->degree-1;
                root->parent->child_cut=true;
                root->parent=NULL;
                meld(head,root);
                if(head->val<root->val)
                {
                    head=root;
                }
                return 1;
            }
            while(root->parent!=NULL && root->parent->child_cut!=false)
            {
                if(root->link_list_left==root)
                {
                    root->parent->link_child=NULL;
                }
                else
                {
                    root->parent->link_child=root->link_list_left;
                    root->link_list_left->link_list_right=root->link_list_right;
                    root->link_list_right->link_list_left=root->link_list_left;
                    root->link_list_left=root;
                    root->link_list_right=root;
                }
                root->parent->degree=root->parent->degree-1;
                struct node *temp=root->parent;
                root->parent=NULL;
                meld(head,root);
                if(head->val<root->val)
                {
                    head=root;
                }
                root=temp;
            }
            if(root!=NULL && root->parent!=NULL)
            {
                root->child_cut=true;//edited here
            }
        }
    }
    return 0;
}

int main(int argc,char * args[])
{
    fstream ofile;
    ofstream ifile;
    ifile.open("output_file.txt");
    if(!ifile)
    {
        std::cout<<"The File to write was not able to open";
        return -1;
    }
    ofile.open(args[1]);
    if(!ofile)
    {
        std::cout<<"The file can not be opened";
        return -1;
    }
    int te=0;
    while(!ofile.eof())
    {
        te++;
        string temp;
        getline(ofile,temp);
        int flag=0;
        int i=1;
        if(temp=="stop"||temp=="STOP")
        {
            return 0;
        }
        if(temp[flag]=='#')
        {
            while(i<temp.length())
            {
                if(temp[i]==' ')
                {
                    string temp1=temp.substr(flag+1,i-flag-1);//this is used to segregate the name from the string
                    int freq=atoi(temp.substr(i+1,temp.length()-1).c_str());
                    std::unordered_map<std::string,struct node *>::const_iterator got = umap.find (temp1);
                    if(got!=umap.end())
                    {
                        increasekey(got->second,freq);
                        ++i;
                    }
                    else
                    {
                        struct node *temp=add(temp1,freq);
                        umap.insert(make_pair(temp1,temp));
                    }
                }
                ++i;
            }
        }
        else
        {
            vector<struct node *>saving;
            saving.clear();
            int freq=atoi(temp.substr(0,temp.length()).c_str());
            while(freq--)
            {
                if(head!=NULL)
                    saving.push_back(remove_max());
            }
            int i=0;
            while(i<saving.size())
            {
                    ifile<<saving[i]->key;
                    //std::cout<<saving[i]->key<<",";
                    if(i<(saving.size()-1))
                    {
                       ifile<<",";
                    }
                    saving[i]->parent=NULL;
                    saving[i]->link_child=NULL;
                    saving[i]->child_cut=false;
                    saving[i]->degree=0;
                    saving[i]->link_list_right=saving[i];
                    saving[i]->link_list_left=saving[i];
                    if(head==NULL && saving[i]!=NULL)
                    {
                        head=saving[i];
                    }
                    else
                    {
                        if(saving[i]!=NULL)
                        {
                            meld(head,saving[i]);
                            if(saving[i]->val>head->val)
                            {
                                head=saving[i];
                            }
                        }
                    }
                ++i;
            }
            //std::cout<<"\n";
            ifile<<"\n";
            ifile.flush();
        }
    }
    ifile.close();
    ofile.close();
    return 0;
}
