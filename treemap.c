#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap *new = (TreeMap *)malloc(sizeof(TreeMap));
    new -> lower_than = lower_than;
    new -> root = NULL;
    new -> current = new -> root;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  
  if(searchTreeMap(tree, key)){
    return;
  }
  TreeNode *node = createTreeNode(key, value);
  tree -> current = tree -> root;
  while(1){
    if(tree -> lower_than(key, tree -> current -> pair -> key)){
      if(tree -> current -> left != NULL){
        tree -> current = tree -> current -> left;
      }else{
        node -> parent = tree -> current;
        tree -> current -> left = node;
        tree -> current = tree -> current -> left;
        break;
      }
    }else if(tree -> lower_than(tree -> current -> pair -> key,key)){
      if(tree -> current -> right != NULL){
        tree -> current = tree -> current -> right;
      }else{
        node -> parent = tree -> current;
        tree -> current -> right = node;
        tree -> current = tree -> current -> right;
        break;
      }
    }else{
      break;
    }
  }

}

TreeNode * minimum(TreeNode * x){
    while(x -> left != NULL){
      x = x -> left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node -> right == NULL && node -> left == NULL){
    if(tree ->lower_than(tree -> current -> parent -> pair -> key, node ->pair->key)){
      tree -> current -> parent -> right = NULL;
    }else{
      tree -> current -> parent -> left = NULL;
    }
  }else if(node -> right != NULL && node -> left == NULL){
    if(tree ->lower_than(tree -> current -> parent -> pair ->           key, node ->pair->key)){
      node -> right -> parent = tree -> current -> parent;
      tree -> current -> parent -> right = node -> right;
      
    }else{
      node -> right -> parent = tree -> current -> parent;
      tree -> current -> parent -> left = node -> right;

    }
  }else if(node -> right == NULL && node -> left != NULL){
    if(tree ->lower_than(tree -> current -> parent -> pair ->           key, node ->pair->key)){
      node -> left -> parent = tree -> current -> parent;
      tree -> current -> parent -> right = node -> left;
    }else{
      node -> left -> parent = tree -> current -> parent;
      tree -> current -> parent -> left = node -> left;

    }
  }else if(node -> right != NULL && node -> left != NULL){
    node = minimum(node -> right);
    
  }

  
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode *aux = tree->root;
  while (aux != NULL){
    if(tree -> lower_than(key, aux->pair->key)){
      aux = aux -> left;
    }else if(tree -> lower_than(aux->pair->key,key)){
      aux = aux -> right;
    }else{
      tree -> current = aux;
      return aux->pair;
    }
  }
  
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
