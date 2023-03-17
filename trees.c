
#include <stdio.h>
#include <stdlib.h>
 
struct node {
    int key;
    struct node *left, *right;
};
 
//Agac olusturuluyor
struct node* newNode(int item)
{
    struct node* temp
        = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
 
//Agacýn inorder (kucukten buyuge gezen ve yazdýran) fonksiyonu
void inorder(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

//Agaca yeni dugum ekleme fonksiyonu
struct node* insert(struct node* node, int key)
{
   
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
 
    return node;
}
//Bir düðümün kendi silsilesinden en uzak yaprak düðüme olan uzaklýðýný bulan fonksiyon
int height(struct node* node)
{
    if (node == NULL)
        return 0;
    else {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
 
        /* use the larger one */
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

void printCurrentLevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->key);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}
//En ust dugumden alta dogru sýrasýyla yazan (level-order) fonksiyon 
void printLevelOrder(struct node* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}
//max dugumu bulan fonksiyon
int maxValue(struct node* node)
{  
    struct node* current = node;
    while (current->right != NULL)
        current = current->right;
     
    return (current->key);
}

//Min dugumu bulan recursive fonksiyon
int minValue(struct node* node)
{
    if (node->left == NULL)
        return node->key;
    return minValue(node->left);
}

int KardesDugum(struct node* node, int k) {
    int sib = -1;
    while (node) {
        if (node->key == k) {
            return sib;
        }
        if (k > node->key) {
            sib = node->left->key;
            node = node->right;
        } else {
            sib = node->right->key;
            node = node->left;
        }
    }
    return sib;
}

int AtaDugum(struct node* node, int num) {
	if (node == NULL)
   	 return;
  
	if (node->key == num)
    	return;
  
	if (AtaDugum(node->left, num) ||
    	AtaDugum(node->right, num) ) {
      printf("%d ", node->key);
      return;
	}
	else {
      return;
	}
}
 
int main()
{
	struct node* root = NULL;
	root = insert(root, 50); // ilk dugum olusturuluyor
	int choice,cont,data;
	do{
		printf("Secim Yapiniz:(1-Ekleme Yap/2-In-Order dolasma/3-Level-order dolasma/4-Max deger ve kardes,ata dugumu/5-Min deger ve kardes,ata dugumu)\n");
		scanf("%d",&choice);
		if(choice==1){
			printf("Girmek istediginiz sayi: ");
			scanf("%d",&data);
			insert(root,data);
		}
		else if(choice==2){
			inorder(root);
		}
		
		else if(choice==3){
			printLevelOrder(root);
		} 
		else if(choice==4){
			int buyuk=maxValue(root);
			printf("En buyuk dugum: %d\n",buyuk);
			printf("En buyuk dugumun kardesleri: %d ",KardesDugum(root,buyuk));
			printf("\nEn buyuk dugumun atalari: ");
			AtaDugum(root,buyuk);
		}
		else if(choice==5){
			int kucuk=minValue(root);
			printf("En kucuk dugum: %d\n",kucuk);
			printf("En kucuk dugumun kardesleri: %d ",KardesDugum(root,kucuk));
			printf("\nEn kucuk dugumun atalari: ");
			AtaDugum(root,kucuk);
		}
		printf("\nIf you want to continue, enter 1\nIf you want to exit, enter 0: \n\n");
		scanf("%d",&cont);
	}while(cont);

    return 0;
}
