#include <stdio.h>
#include <stdlib.h>

#define MAX_PHOTO_COMBOS 39
#define MAX_PHOTOS 20
#define MAX_PHOTO_CATEGORIES 3

struct Link
{
  int photoSrc;
  int photoDest;
  int photoSimilarity;
};

int qsortCompare(const void* a, const void* b);                                 // qsort comparision function
int disjointFind(int x, int *photoSet);                                         // Implementation of the find2 operation of Disjoint DS
int disjointUnion(int representativeX, int representativeY, int *photoSet, int *photoSetHeight);  // Implementation of the Union3 operation of Disjoint DS

int qsortCompare(const void* a, const void* b)
{
  struct Link* x = (struct Link*)a;
  struct Link* y = (struct Link*)b;
  return x->photoSimilarity < y->photoSimilarity;
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
      photoSetHeight[representativeX]++;
    }
    else
    {
      photoSet[representativeX] = representativeY;
      photoSetHeight[representativeY]++;
    }
  }
}

int main (int argc, char *argv[])
{
  struct Link photoLink[MAX_PHOTO_COMBOS], resultPhotoSet[MAX_PHOTO_COMBOS];
  int photoSet[MAX_PHOTOS] = {0};                   // Disjoint Data set for the photos
  int photoSetHeight[MAX_PHOTOS] = {0};             // Height maintained for the photosets
  int i=0, j=0;
  int ucomp, vcomp;
  int representatives[MAX_PHOTO_CATEGORIES];        // Array to store root representative for each category
  int photoSetCategory[MAX_PHOTO_CATEGORIES][MAX_PHOTOS];                       // Resulting Photo Categories and photos in those categories
  int tempRepresentative[MAX_PHOTO_CATEGORIES] = {9999};  // Initialize with default

  for (i = 0; i < MAX_PHOTOS; i++)                  // Result photo set to be empty and default all photos as individual sets
  {
    photoSet[i] = i;
    resultPhotoSet[i].photoSrc = 0; resultPhotoSet[i].photoDest = 0; resultPhotoSet[i].photoSimilarity = 0;
  }

  for (i = 0; i < MAX_PHOTO_CATEGORIES; i++)                  // Result photo set to be empty and default all photos as individual sets
  {
    representatives[i] = 9999;                                // Set default representative
    for (j = 0; j < MAX_PHOTOS; j++)
    {
      photoSetCategory[i][j] = 9999;                          // Set default value
    }
  }

  photoLink[0].photoSrc = 1; photoLink[0].photoDest = 2; photoLink[0].photoSimilarity = 80;
  photoLink[1].photoSrc = 5; photoLink[1].photoDest = 9; photoLink[1].photoSimilarity = 73;
  photoLink[2].photoSrc = 9; photoLink[2].photoDest = 13; photoLink[2].photoSimilarity = 69;
  photoLink[3].photoSrc = 2; photoLink[3].photoDest = 3; photoLink[3].photoSimilarity = 10;
  photoLink[4].photoSrc = 5; photoLink[4].photoDest = 7; photoLink[4].photoSimilarity = 20;
  photoLink[5].photoSrc = 5; photoLink[5].photoDest = 2; photoLink[5].photoSimilarity = 74;
  photoLink[6].photoSrc = 9; photoLink[6].photoDest = 18; photoLink[6].photoSimilarity = 15;
  photoLink[7].photoSrc = 13; photoLink[7].photoDest = 14; photoLink[7].photoSimilarity = 21;
  photoLink[8].photoSrc = 9; photoLink[8].photoDest = 1; photoLink[8].photoSimilarity = 92;
  photoLink[9].photoSrc = 13; photoLink[9].photoDest = 2; photoLink[9].photoSimilarity = 59;
  photoLink[10].photoSrc = 20; photoLink[10].photoDest = 4; photoLink[10].photoSimilarity = 6;
  photoLink[11].photoSrc = 18; photoLink[11].photoDest = 17; photoLink[11].photoSimilarity = 17;
  photoLink[12].photoSrc = 11; photoLink[12].photoDest = 3; photoLink[12].photoSimilarity = 74;
  photoLink[13].photoSrc = 7; photoLink[13].photoDest = 18; photoLink[13].photoSimilarity = 83;
  photoLink[14].photoSrc = 7; photoLink[14].photoDest = 12; photoLink[14].photoSimilarity = 27;
  photoLink[15].photoSrc = 1; photoLink[15].photoDest = 10; photoLink[15].photoSimilarity = 16;
  photoLink[16].photoSrc = 5; photoLink[16].photoDest = 15; photoLink[16].photoSimilarity = 47;
  photoLink[17].photoSrc = 20; photoLink[17].photoDest = 14; photoLink[17].photoSimilarity = 94;
  photoLink[18].photoSrc = 14; photoLink[18].photoDest = 18; photoLink[18].photoSimilarity = 77;
  photoLink[19].photoSrc = 2; photoLink[19].photoDest = 4; photoLink[19].photoSimilarity = 30;
  photoLink[20].photoSrc = 11; photoLink[20].photoDest = 14; photoLink[20].photoSimilarity = 62;
  photoLink[21].photoSrc = 3; photoLink[21].photoDest = 20; photoLink[21].photoSimilarity = 85;
  photoLink[22].photoSrc = 11; photoLink[22].photoDest = 7; photoLink[22].photoSimilarity = 62;
  photoLink[23].photoSrc = 6; photoLink[23].photoDest = 10; photoLink[23].photoSimilarity = 87;
  photoLink[24].photoSrc = 12; photoLink[24].photoDest = 15; photoLink[24].photoSimilarity = 81;
  photoLink[25].photoSrc = 3; photoLink[25].photoDest = 19; photoLink[25].photoSimilarity = 39;
  photoLink[26].photoSrc = 9; photoLink[26].photoDest = 8; photoLink[26].photoSimilarity = 45;
  photoLink[27].photoSrc = 19; photoLink[27].photoDest = 4; photoLink[27].photoSimilarity = 65;
  photoLink[28].photoSrc = 8; photoLink[28].photoDest = 16; photoLink[28].photoSimilarity = 70;
  photoLink[29].photoSrc = 15; photoLink[29].photoDest = 17; photoLink[29].photoSimilarity = 64;
  photoLink[30].photoSrc = 1; photoLink[30].photoDest = 11; photoLink[30].photoSimilarity = 32;
  photoLink[31].photoSrc = 11; photoLink[31].photoDest = 6; photoLink[31].photoSimilarity = 43;
  photoLink[32].photoSrc = 12; photoLink[32].photoDest = 6; photoLink[32].photoSimilarity = 87;
  photoLink[33].photoSrc = 12; photoLink[33].photoDest = 19; photoLink[33].photoSimilarity = 70;
  photoLink[34].photoSrc = 7; photoLink[34].photoDest = 16; photoLink[34].photoSimilarity = 39;
  photoLink[35].photoSrc = 13; photoLink[35].photoDest = 6; photoLink[35].photoSimilarity = 22;
  photoLink[36].photoSrc = 4; photoLink[36].photoDest = 16; photoLink[36].photoSimilarity = 68;
  photoLink[37].photoSrc = 17; photoLink[37].photoDest = 10; photoLink[37].photoSimilarity = 56;
  photoLink[38].photoSrc = 19; photoLink[38].photoDest = 15; photoLink[38].photoSimilarity = 71;

  qsort(&photoLink[0], MAX_PHOTO_COMBOS, sizeof(photoLink[0]), qsortCompare);         // Sort in decreasing order

  printf("After Sorting:\n");
  for (i = 0; i < MAX_PHOTO_COMBOS; i++)
  {
    printf("(%d, %d) = %d\n", photoLink[i].photoSrc, photoLink[i].photoDest, photoLink[i].photoSimilarity);
  }

  printf("*********************************\n");

  for (i = 0; i < MAX_PHOTO_COMBOS; i++)
  {
    printf("Checking: photoSrc=%d photoDest=%d\n", photoLink[i].photoSrc-1, photoLink[i].photoDest-1);
    ucomp = disjointFind(photoLink[i].photoSrc-1, &photoSet[0]);                // Photo number starts from 1 to 20, let's make it 0 to 19
    vcomp = disjointFind(photoLink[i].photoDest-1, &photoSet[0]);               // Photo number starts from 1 to 20, let's make it 0 to 19

    printf("ucomp=%d vcomp=%d\n", ucomp, vcomp);

    if (ucomp != vcomp)                                                         // If not in same set, add them
    {
      printf("YES, Union this points: %d & %d\n", ucomp, vcomp);
      if (photoLink[i].photoSimilarity >= 50)                                   // Only if matching value is above 50, should not matter even if we remove
      {
        disjointUnion(ucomp, vcomp, &photoSet[0], &photoSetHeight[0]);
      }
    }
  }

  printf("PHOTOSET::\n [ ");
  for (i = 0; i < MAX_PHOTOS; i++)                                               // Result photo set to be empty and default all photos as individual sets
  {
    printf("%d -> %d, ", i+1, photoSet[i]+1);
  }
  printf("]\n");

  printf("RESULT::\n");
  int intitialControlFlag[MAX_PHOTO_CATEGORIES] = {0};
  int k = 0,l = 0,m = 0;
  for (i = 0; i < MAX_PHOTOS; i++)                                               // Categories the photos differently based on their representative root
  {
    if (intitialControlFlag[0] == 0)
    {
      tempRepresentative[0] = disjointFind(i, &photoSet[0]);
      intitialControlFlag[0] = 1;
    }

    if (tempRepresentative[0] != disjointFind(i, &photoSet[0]))
    {
      if (intitialControlFlag[1] == 0)
      {
        tempRepresentative[1] = disjointFind(i, &photoSet[0]);
        intitialControlFlag[1] = 1;
      }
      else if (intitialControlFlag[2] == 0)
      {
        tempRepresentative[2] = disjointFind(i, &photoSet[0]);
        intitialControlFlag[2] = 1;
      }
    }

    if (tempRepresentative[0] == disjointFind(i, &photoSet[0]))
    {
      photoSetCategory[0][k++] = i;
    }
    else if (tempRepresentative[1] == disjointFind(i, &photoSet[0]))
    {
      photoSetCategory[1][l++] = i;
    }
    else
    {
      photoSetCategory[2][m++] = i;
    }
  }

  for (i = 0; i < MAX_PHOTO_CATEGORIES; i++)                                               // Result photo set to be empty and default all photos as individual sets
  {
    printf("\ncategory-%d: ", i+1);
    for (j = 0; j < MAX_PHOTOS; j++)
    {
      if (photoSetCategory[i][j] != 9999)
      {
        printf(" P%d", photoSetCategory[i][j]+1);
      }
      else
      {
        break;
      }
    }
    printf(" And Total Photos: %d\n", j);
  }
  printf("\n");
  return 0;
}
