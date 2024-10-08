// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();
char rand_parent_allele(char parentAllele1, char parentAllele2);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    //Allocate memory for new person
    person *newPerson = malloc(sizeof(person));

    // Generation with parent data
    if (generations > 1)
    {
        int parent_generation = generations - 1;
        //Recursively create blood type histories for parents
        newPerson->parents[0] = create_family(parent_generation);
        newPerson->parents[1] = create_family(parent_generation);

        //Randomly assign child alleles based on parents
        newPerson->alleles[0] = rand_parent_allele(newPerson->parents[0]->alleles[0], newPerson->parents[0]->alleles[1]);
        newPerson->alleles[1] = rand_parent_allele(newPerson->parents[1]->alleles[0], newPerson->parents[1]->alleles[1]);
    }

    // Generation without parent data
    else
    {
        //Set parent pointers to NULL
        newPerson->parents[0] = NULL;
        newPerson->parents[1] = NULL;

        //Randomly assign alleles
        newPerson->alleles[0] = random_allele();
        newPerson->alleles[1] = random_allele();
    }

    //Return newly created person
    return newPerson;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    //Handle base case
    if (p->parents[0] == NULL)
    {
        //Free parents
        free(p->parents[0]);
    }
    else
    {
        free_family(p->parents[0]);
    }

    if (p->parents[1] == NULL)
    {
        free(p->parents[1]);
    }
    else
    {
        free_family(p->parents[1]);
    }

    //Free child
    free(p);

}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

char rand_parent_allele(char parentAllele1, char parentAllele2)
{
    int r = rand() % 2;

    if (r == 0)
    {
        return parentAllele1;
    }
    else
    {
        return parentAllele2;
    }

}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
