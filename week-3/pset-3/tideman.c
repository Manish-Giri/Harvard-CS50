// Pset 3 Tideman - https://cs50.harvard.edu/x/2020/psets/3/tideman/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void print_pairs(void);
void print_preferences(void);
int get_strength(int);
bool does_pair_exist(int, int);
bool cyclic(int, int);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    int candidate_pos = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            candidate_pos = i;
            break;
        }

    }
    if (candidate_pos != -1)
    {
        ranks[rank] = candidate_pos;
        return true;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int row = -1, col = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        row = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {

            col = ranks[j];
            preferences[row][col] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int vote_1 = -1, vote_2 = -1;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // pair[i][j]
            vote_1 = preferences[i][j];
            vote_2 = preferences[j][i];

            // if pair <i,j> already exists in pairs OR pair is a tie
            // ignore and continue
            if ((does_pair_exist(i, j) || vote_1 == vote_2))
            {
                continue;
            }

            // scenario 1 - i wins over j
            if (vote_1 > vote_2)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if (vote_2 > vote_1)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;

            }

        }

    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // print pairs
    // print_pairs();
    // print preferences[][]
    // print_preferences();

    // sort pairs by decreasing strength

    // sort in descending order using selection sort
    int largest_strength = -1, largest_idx = -1, j = -1;
    pair temp;
    for (int i = 0; i < pair_count; i++)
    {

        largest_strength = -1;

        for (j = i; j < pair_count; j++)
        {

            if (get_strength(j) > largest_strength)
            {
                largest_strength = get_strength(j);
                largest_idx = j;
            }

        }

        // swap i and j
        temp = pairs[largest_idx];
        pairs[largest_idx] = pairs[i];
        pairs[i] = temp;

    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int first, second;
    for (int i = 0; i < pair_count; i++)
    {
        first = pairs[i].winner;
        second = pairs[i].loser;
        // lock pair if it doesn't create a cycle
        if (!cyclic(first, second))
        {
            locked[first][second] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO

    // in locked[][] array, if a candidate has false in all their [j] cells in [i][j]
    // then that candidate is the winnder
    // example - cor C0, [0][0], [1][0] and [2][0] must be false
    bool is_curr_winner;
    for (int i = 0; i < candidate_count; i++)
    {
        is_curr_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_curr_winner = false;
                break;
            }

        }
        if (is_curr_winner)
        {
            printf("%s\n", candidates[i]);
        }

    }
    return;
}

void print_pairs()
{
    printf("\nPrinting pairs...\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%d -> %d\n", pairs[i].winner, pairs[i].loser);
    }
}

void print_preferences()
{
    printf("-----PREFERENCES------\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d  ", preferences[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int get_strength(int pair_num)
{
    int winnerIdx = pairs[pair_num].winner;
    int loserIdx = pairs[pair_num].loser;

    // get strength of winner and loser from preferences
    return preferences[winnerIdx][loserIdx] - preferences[loserIdx][winnerIdx];
}

bool does_pair_exist(int first, int second)
{
    // given a pair <i,j> make sure it doesn't already exist in pairs[]
    int winner, loser;
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;

        if ((winner == first && loser == second) || (loser == first && winner == second))
        {
            return true;
        }

    // after loop - pair doesn't exist
    return false;
}

bool cyclic(int w, int l)
{

    // base case -
    if (locked[l][w])
    {
        return true;
    }


    // if loser is not a winner in locked, no cycle
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][w])
        {
            if (cyclic(i, l))
            {
                return true;
            }

        }

    }
    return false;
}
