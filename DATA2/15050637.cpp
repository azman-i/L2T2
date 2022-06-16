#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define FALSE_VALUE 0
#define TRUE_VALUE 1
using namespace std;
struct treeNode
{
    int item;
    struct treeNode *parent;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
   char color;
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


//struct treeNode * searchItem(struct treeNode * node, int item)
//{
//    if(node==0) return 0;
//    if(node->item==item) return node; //found, return node
//    struct treeNode * t = 0;
//    if(item < node->item)
//        t = searchItem(node->left, item); //search in the left sub-tree
//    else
//        t = searchItem(node->right, item); //search in the right sub-tree
//    return t;
//};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->parent=0;
    node->left = 0;
    node->right = 0;
    node->color='r';
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        root->parent=0;
        return newNode;
    }

    //if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        newNode->parent=node;
        return newNode;
    }

    if(item>=node->item && node->right==0) //insert as the right child
    {
        cout<<"inside1"<<endl;
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        newNode->parent=node;
          cout<<"inside2"<<endl;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}


void Left_Rotate(struct treeNode *node)
{
    if(node->right==0)
    {
        return;
    }
    else
        {
            struct treeNode *temp=node->right;
         if(temp->left!=0)
         {
             node->right=temp->left;
             temp->left->parent=node;
         }
        else
            node->right=0;
        if(node->parent!=0)
        {
            temp->parent=node->parent;
        }
        if(node->parent==0)
            root=temp;
        else
        {
            if(node==node->parent->left)
            {
                node->parent->left=temp;
            }
            else
                node->parent->right=temp;
        }
        temp->left=node;
        node->parent=temp;
    }
}
void Right_rotate(struct treeNode *node)
{
     if(node->left==NULL)
          return ;
     else
     {
        struct treeNode *temp=node->left;
         if(temp->right!=NULL)
         {
                  node->left=temp->right;
                  temp->right->parent=node;
         }
         else
                node->left=NULL;
         if(node->parent!=NULL)
                 temp->parent=node->parent;
         if(node->parent==NULL)
               root=temp;
         else
         {
             if(node==node->parent->left)
                   node->parent->left=temp;
             else
                   node->parent->right=temp;
         }
         temp->right=node;
         node->parent=temp;
     }
}
void insert_fix(struct treeNode *n,int item)
{
    struct treeNode *node=insertItem(n,item);
    cout<<"hello1"<<endl;
    if(root==node)
    {
        node->color='b';
        printf("hello");
        return;
    }
    cout<<"hello2"<<endl;
    while(node->parent!=0 && node->parent->color=='r')
    {
        struct treeNode *grandnode=node->parent->parent;
        if(grandnode->left==node->parent)
        {
            if(grandnode->right!=0)
            {
                struct treeNode *temp;
                temp=grandnode->right;
                if(temp->color=='r')
                {
                    node->parent->color='b';
                    temp->color='b';
                    grandnode->color='r';
                    node=grandnode;
                }
            }

            else
            {
                if(node->parent->right=node)
                {
                    node=node->parent;
                    Left_Rotate(node);
                }
                node->parent->color='b';
                            grandnode->color='r';
                            Right_rotate(grandnode);
            }


     cout<<"hello3"<<endl;

        }
        else
        {
                       if(grandnode->left!=0)
                        {
                          struct treeNode *temp=grandnode->left;
                             if(temp->color=='r')
                             {
                                  node->parent->color='b';
                                  temp->color='b';
                                  grandnode->color='r';
                                  node=grandnode;
                             }
                        }
                        else
                        {
                            if(node->parent->left==node)
                            {
                                node=node->parent;
                                Right_rotate(node);
                            }
                            node->parent->color='b';
                            grandnode->color='r';
                            Left_Rotate(grandnode);
                        }
        }
        root->color='b';
    }


}

void display(struct treeNode *p)
{
     if(root==NULL)
     {
          cout<<"\nEmpty Tree.";
          return ;
     }
     if(p!=NULL)
     {
                cout<<"\n\t NODE: ";
                cout<<"\n Key: "<<p->item;
                cout<<"\n Colour: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->item;
                else
                       cout<<"\n There is no parent of the node.  ";
                if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->item;
                else
                       cout<<"\n There is no right child of the node.  ";
                if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->item;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;
    if(p->left)
    {
                 cout<<"\n\nLeft:\n";
     display(p->left);
    }
    /*else
     cout<<"\nNo Left Child.\n";*/
    if(p->right)
    {
     cout<<"\n\nRight:\n";
                 display(p->right);
    }
    /*else
     cout<<"\nNo Right Child.\n"*/
     }
}
void disp()
{
     display(root);
}
int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}

void FixDelete(struct treeNode *node)
{
    struct treeNode *s;
    while(node!=root&&node->color=='b')
    {
          if(node->parent->left==node)
          {
                  s=node->parent->right;
                  if(s->color=='r')
                  {
                         s->color='b';
                         node->parent->color='r';
                         Left_Rotate(node->parent);
                         s=node->parent->right;
                  }
                  if(s->right->color=='b'&&s->left->color=='b')
                  {
                         s->color='r';
                         node=node->parent;
                  }
                  else
                  {
                      if(s->right->color=='b')
                      {
                             s->left->color=='b';
                             s->color='r';
                             Right_rotate(s);
                             s=node->parent->right;
                      }
                      s->color=node->parent->color;
                      node->parent->color='b';
                      s->right->color='b';
                      Left_Rotate(node->parent);
                      node=root;
                  }
          }
          else
          {
                  s=node->parent->left;
                  if(s->color=='r')
                  {
                        s->color='b';
                        node->parent->color='r';
                        Right_rotate(node->parent);
                        s=node->parent->left;
                  }
                  if(s->left->color=='b'&&s->right->color=='b')
                  {
                        s->color='r';
                        node=node->parent;
                  }
                  else
                  {
                        if(s->left->color=='b')
                        {
                              s->right->color='b';
                              s->color='r';
                              Left_Rotate(s);
                              s=node->parent->left;
                        }
                        s->color=node->parent->color;
                        node->parent->color='b';
                        s->left->color='b';
                        Right_rotate(node->parent);
                        node=root;
                  }
          }
       node->color='b';
       root->color='b';
    }
}
struct treeNode* successor(struct treeNode *node)
{
      struct treeNode *node1=NULL;
     if(node->left!=0)
     {
         node1=node->left;
         while(node1->right!=0)
              node1=node1->right;
     }
     else
     {
         node1=node->right;
         while(node1->left!=NULL)
              node1=node1->left;
     }
     return node1;
}



void deleteItem(int it)
{
     if(root==0)
     {
           cout<<"\nEmpty Tree." ;
           return ;
     }

     struct treeNode *node;
     node=root;
     struct treeNode *node1=NULL;
     struct treeNode  *node2=NULL;
     int search=0;
     while(node!=NULL&&search==0)
     {
           if(node->item==it)
               search=1;
           if(search==0)
           {
                 if(node->item<it)
                    node=node->right;
                 else
                    node=node->left;
           }
     }
     if(search==0)
     {
            cout<<"\nElement Not Found.";
            return ;
     }
     else
     {

         if(node->left==0||node->right==0)
              node1=node;
         else
              node1=successor(node);
         if(node1->left!=0)
              node2=node1->left;
         else
         {
              if(node1->right!=0)
                   node2=node1->right;
              else
                   node2=0;
         }
         if(node2!=0)
              node2->parent=node1->parent;
         if(node1->parent==0)
              root=node2;
         else
         {
             if(node1==node1->parent->left)
                node1->parent->left=node2;
             else
                node1->parent->right=node2;
         }
         if(node1!=node)
         {
             node->color=node1->color;
             node->item=node1->item;
         }
         if(node1->color=='b')
             FixDelete(node2);
     }
}

//int calcHeight(int item) //return height of an item in the tree
//{
//    struct treeNode * node = 0;
//    node = searchItem(root, item);
//    if(node==0) return -1; //not found
//    else return calcNodeHeight(node);
//}

//int getSize(struct treeNode * node)
//{
//    int sum=0;
//       if(node==0)
//        return 0;
//       else
//       {
//           return 1+getSize(node->left)+getSize(node->right);
//
//       }
//}
//int calcNodeDepth(struct treeNode * node) //return depth of a node
//{
//    //write your codes here
//    struct treeNode *node1= 0;
//    int count=0;
//    node1=root;
//    while(1)
//    {if(node->item<node1->item)
//    {
//        node1=node1->left;
//        count++;
//    }
//    if(node->item>node1->item)
//    {
//        node1=node1->right;
//        count++;
//    }
//    if(node->item==node1->item)
//    {
//        return count;
//    }
//    }
//}
//
//
//int calculationNode(int item)
//{
//    struct treeNode * node = 0;
//      node=root;
//    while(1)
//    {if(item<node->item)
//    {
//        node=node->left;
//
//    }
//    if(item>node->item)
//    {
//        node=node->right;
//           }
//    if(node->item==item)
//    {
//        return calcNodeDepth(node);
//    }
//    }
//}
//
//int calcDepth(int item)//return depth of an item in the tree
//{
//    struct treeNode *node = 0;
//    int count=0;
//    node=root;
//    while(1)
//    {if(item<node->item)
//    {
//        node=node->left;
//        count++;
//    }
//    if(item>node->item)
//    {
//        node=node->right;
//        count++;
//    }
//    if(node->item==item)
//    {
//        return count;
//    }
//    }
//}
//struct treeNode *getMinItemwithnode(struct treeNode *node)
//{
//    node=node->right;
//    while(node->left!=0)
//        node=node->left;
//    return node;
//}
//int deleteItem(struct treeNode * node, int item)
//{
//    //write your code here, return TRUE, FALSE
//
//    struct treeNode *parent=0;
//
//      if(searchItem(root,item)!=0)
//    {if((parent==0)&&(node==0))
//        return -1;
//        while(1)
//        {
//            if(item<node->item)
//                {
//                    parent=node;
//                node=node->left;
//            }
//            if(item>node->item)
//                {  parent=node;
//                    node=node->right;
//                }
//            if(item==node->item)
//            {
//
//               if((node->left==0)&&(node->right!=0)&&(parent!=0))
//               {
//
//                   parent->left=0;
//                   parent->right=node->right;
//                   break;
//               }
//               if((node->left==0)&&(node->right!=0)&&(parent==0))
//               {
//                   root=node->right;
//                   break;
//               }
//                if((node->right==0)&&(node->left!=0)&&(parent!=0))
//                {
//
//                    parent->left=node->left;
//                    parent->right=0;
//                    break;
//                }
//                if((node->right==0)&&(node->left!=0)&&(parent==0))
//                {
//                     root=node->left;
//                     break;
//                }
//                if((node->left==0)&&(node->right==0)&&(parent!=0))//alright
//                {
//
//                    if(parent->item<node->item)
//                        {parent->right=0;
//
//                        }
//                    if(parent->item>node->item)
//                        {parent->left=0;
//
//                        }
//                        break;
//                }
//                if((node->left!=0)&&(node->right!=0))//alright
//                {
//
//               struct treeNode *returntree;
//
//                   struct treeNode *parenttree=node;
//                   returntree=node->right;
//                   while(returntree->left!=0)
//                      {
//                          parenttree=returntree;
//                          returntree=returntree->left;
//                      }
//
//                      if(parenttree==node)
//                      {
//
//                          parenttree->item=returntree->item;
//                          parenttree->right=returntree->right;
//                          break;
//                      }
//                      else{
//
//                        node->item=returntree->item;
//                        parenttree->left=returntree->right;
//                    break;
//                      }
//
//                }
//                if((parent==0)&&(node->left==0)&&(node->right==0))//alright
//                    {
//                    root=0;
//                    break;
//                    }
//            }
//
//
//        }
//
//}
//else
//    return -1;
//}



//int getMinItem() //returns the minimum item in the tree
//{
//    //write your codes here
//    struct treeNode * node = root;
//    while(node->left!=0)
//    {
//       node=node->left;
//    }
//    return node->item;
//}
//
//int getMaxItem() //returns the maximum item in the tree
//{
//    //write your codes here
//    struct treeNode * node = root;
//    if(root!=0){
//    while(node->right!=0)
//    {
//       node=node->right;
//    }
//    return node->item;
//    }
//}
//
//int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
//{
//   if(node==0)
//    return 0;
//   if(node->item>=leftBound&&node->item<=rightBound)
//    return 1+rangeSearch(node->left,leftBound,rightBound)+rangeSearch(node->right,leftBound,rightBound);
//   if(node->item<leftBound)
//    rangeSearch(node->right,leftBound,rightBound);
//   else
//    rangeSearch(node->left,leftBound,rightBound);
//
//}
//

void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
//    for(int i=0;i<height;i++)printf("   ");
//    printf("%03d ( %c)\n",node->item,node->color);
        printf("%d (%c)",node->item,node->color);
    //print right sub-tree
    printInOrder(node->right, height-1);
}


int searchItem(struct treeNode *node,int item)
{
    while(true)
    {
        if(node==0)
            return 0;
        if(item<node->item)
        {
            node=node->left;
        }
        else if(item>node->item)
        {
            node=node->right;
        }
        else if(item==node->item)
            return 1;
    }
}

int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit.   8.getsize\n");
         printf("9.Calculation item height   10.Minimum  11.Maximum\n");
        printf("12.Range search     13.Delete item   14.calculation Node Height\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insert_fix(root, item);
        }
//        else if(ch==2)
//        {
//            int item;
//            scanf("%d", &item);
//            deleteItem(root, item);
//            disp();
//        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
           int b= searchItem(root, item);
            if(b!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
//        else if(ch==4)
//        {
//            int height = calcNodeHeight(root);
//            printf("Height of tree = %d\n", height);
//        }
//        else if(ch==5)
//        {
//            int item;
//            scanf("%d", &item);
//            int height = calcHeight(item);
//            printf("Height of %d = %d\n", item, height);
//        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
//        else if(ch==6)
//        {
//            break;
//        }
//        else if(ch==8)
//        {
//            int item;
//            //scanf("%d",&item);
//            printf("%d\n",getSize(root));
//        }
//        else if(ch==9)
//        {
//            int item;
//            scanf("%d",&item);
//            printf("%d\n",calcDepth(item));
//        }
//        else if(ch==10)
//        {
//            int item;
//            //scanf("%d",&item);
//            printf("%d\n",getMinItem());
//        }
//        else if(ch==11)
//        {
//            int item;
//            //scanf("%d",&item);
//            printf("%d\n",getMaxItem());
//        }
//        else if(ch==12)
//        {
//            int item1,item2;
//            scanf("%d  %d",&item1,&item2);
//            printf("%d\n",rangeSearch(root,item1,item2));
//        }
         else if(ch==13)
        {
            int item1;
            scanf("%d",&item1);
          deleteItem(item1);

        }
//        else if(ch==14)
//        {
//            int item;
//            scanf("%d",&item);
//            printf("%d\n",calculationNode(item));
//        }
//
//    }

}
}
