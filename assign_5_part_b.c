#include <stdio.h>
#include <stdlib.h>

#define MAX_PHOTO_COMBOS 39
#define MAX_PHOTOS 20

struct Link
{
  int src;
  int dest;
  int weight;
};

int qsortCompare(const void* a, const void* b);                                 // qsort comparision function
int disjointFind(int x, int *photoSet);                                         // Implementation of the find2 operation of Disjoint DS
int disjointUnion(int representativeX, int representativeY, int *photoSet, int *photoSetHeight);  // Implementation of the Union3 operation of Disjoint DS

int qsortCompare(const void* a, const void* b)
{
  struct Link* x = (struct Link*)a;
  struct Link* y = (struct Link*)b;
  return x->weight < y->weight;
}

int disjointFind (int x, int *photoSet)
{
  int representative = 0;
  representative = x;

  while (representative != photoSet[representative])
  {
    representative = photoSet[representative];
  }

  return representative;
}

int disjointUnion (int representativeX, int representativeY, int *photoSet, int *photoSetHeight)
{
  if (photoSetHeight[representativeX] == photoSetHeight[representativeY])
  {
    photoSetHeight[representativeX]++;
    photoSet[representativeY] = representativeX;
  }
  else
  {
    if (photoSetHeight[representativeX] > photoSetHeight[representativeY])
    {
      photoSet[representativeY] = representativeX;
    }
    else
    {
      photoSet[representativeX] = representativeY;
    }
  }
}

int main (int argc, char *argv[])
{
  struct Link photoLink[MAX_PHOTO_COMBOS], resultPhotoSet[MAX_PHOTO_COMBOS];
  int photoSet[MAX_PHOTOS] = {0};                   // Disjoint Data set for the photos
  int photoSetHeight[MAX_PHOTOS] = {0};             // Height maintained for the photosets
  int i=0;
  int ucomp, vcomp;

  for (i = 0; i < MAX_PHOTOS; i++)                  // Result photo set to be empty and default all photos as individual sets
  {
    photoSet[i] = i;
    resultPhotoSet[i].src = 0; resultPhotoSet[i].dest = 0; resultPhotoSet[i].weight = 0;
  }

  photoLink[0].src = 1; photoLink[0].dest = 2; photoLink[0].weight = 80;
  photoLink[1].src = 5; photoLink[1].dest = 9; photoLink[1].weight = 73;
  photoLink[2].src = 9; photoLink[2].dest = 13; photoLink[2].weight = 69;
  photoLink[3].src = 2; photoLink[3].dest = 3; photoLink[3].weight = 10;
  photoLink[4].src = 5; photoLink[4].dest = 7; photoLink[4].weight = 20;
  photoLink[5].src = 5; photoLink[5].dest = 2; photoLink[5].weight = 74;
  photoLink[6].src = 9; photoLink[6].dest = 18; photoLink[6].weight = 15;
  photoLink[7].src = 13; photoLink[7].dest = 14; photoLink[7].weight = 21;
  photoLink[8].src = 9; photoLink[8].dest = 1; photoLink[8].weight = 92;
  photoLink[9].src = 13; photoLink[9].dest = 2; photoLink[9].weight = 59;
  photoLink[10].src = 20; photoLink[10].dest = 4; photoLink[10].weight = 6;
  photoLink[11].src = 18; photoLink[11].dest = 17; photoLink[11].weight = 17;
  photoLink[12].src = 11; photoLink[12].dest = 3; photoLink[12].weight = 74;
  photoLink[13].src = 7; photoLink[13].dest = 18; photoLink[13].weight = 83;
  photoLink[14].src = 7; photoLink[14].dest = 12; photoLink[14].weight = 27;
  photoLink[15].src = 1; photoLink[15].dest = 10; photoLink[15].weight = 16;
  photoLink[16].src = 5; photoLink[16].dest = 15; photoLink[16].weight = 47;
  photoLink[17].src = 20; photoLink[17].dest = 14; photoLink[17].weight = 94;
  photoLink[18].src = 14; photoLink[18].dest = 18; photoLink[18].weight = 77;
  photoLink[19].src = 2; photoLink[19].dest = 4; photoLink[19].weight = 30;
  photoLink[20].src = 11; photoLink[20].dest = 14; photoLink[20].weight = 62;
  photoLink[21].src = 3; photoLink[21].dest = 20; photoLink[21].weight = 85;
  photoLink[22].src = 11; photoLink[22].dest = 7; photoLink[22].weight = 62;
  photoLink[23].src = 6; photoLink[23].dest = 10; photoLink[23].weight = 87;
  photoLink[24].src = 12; photoLink[24].dest = 15; photoLink[24].weight = 81;
  photoLink[25].src = 3; photoLink[25].dest = 19; photoLink[25].weight = 39;
  photoLink[26].src = 9; photoLink[26].dest = 8; photoLink[26].weight = 45;
  photoLink[27].src = 19; photoLink[27].dest = 4; photoLink[27].weight = 65;
  photoLink[28].src = 8; photoLink[28].dest = 16; photoLink[28].weight = 70;
  photoLink[29].src = 15; photoLink[29].dest = 17; photoLink[29].weight = 64;
  photoLink[30].src = 1; photoLink[30].dest = 11; photoLink[30].weight = 32;
  photoLink[31].src = 11; photoLink[31].dest = 6; photoLink[31].weight = 43;
  photoLink[32].src = 12; photoLink[32].dest = 6; photoLink[32].weight = 87;
  photoLink[33].src = 12; photoLink[33].dest = 19; photoLink[33].weight = 70;
  photoLink[34].src = 7; photoLink[34].dest = 16; photoLink[34].weight = 39;
  photoLink[35].src = 13; photoLink[35].dest = 6; photoLink[35].weight = 22;
  photoLink[36].src = 4; photoLink[36].dest = 16; photoLink[36].weight = 68;
  photoLink[37].src = 17; photoLink[37].dest = 10; photoLink[37].weight = 56;
  photoLink[38].src = 19; photoLink[38].dest = 15; photoLink[38].weight = 71;

  qsort(&photoLink[0], MAX_PHOTO_COMBOS, sizeof(photoLink[0]), qsortCompare);         // Sort in decreasing order

  printf("After Sorting:\n");
  for (i = 0; i < MAX_PHOTO_COMBOS; i++)
  {
    printf("(%d, %d) = %d\n", photoLink[i].src, photoLink[i].dest, photoLink[i].weight);
  }

  printf("*********************************\n");

  for (i = 0; i < MAX_PHOTO_COMBOS; i++)
  {
    ucomp = disjointFind(photoLink[i].src, &photoSet[0]);
    vcomp = disjointFind(photoLink[i].dest, &photoSet[0]);

    printf("ucomp=%d vcomp=%d\n", ucomp, vcomp);

    if (ucomp != vcomp)       // If not in same set, add them
    {
      printf("YES, Union this points: %d & %d\n", ucomp, vcomp);
      if (photoLink[i].weight > 50)                                             // Only if matching value is above 50, should not matter even if we remove
      {
        disjointUnion(ucomp, vcomp, &photoSet[0], &photoSetHeight[0]);
      }
    }
  }

  printf("RESULT::\n [ ");
  for (i = 0; i < MAX_PHOTOS; i++)                  // Result photo set to be empty and default all photos as individual sets
  {
    printf("%d, ", photoSet[i]+1);
  }
  printf("]\n");
  return 0;
}
