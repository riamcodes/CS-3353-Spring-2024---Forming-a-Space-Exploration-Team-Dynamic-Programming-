#include <iostream>
#include <vector>
//#include <algorithm>
#include "prog4.h"


istream& operator>>(istream& is, Applicant& a);
ostream& operator<<(ostream& os, Applicant& a);

pair<int, vector<Applicant> >pickTeam(int budget, vector< vector<Applicant> >& alist)
{
    //Struct to hold the state of each choice
    // contains total benefit and also list of chosen applicants
    struct chosenState {
        float totalBenefit = 0.0;
        vector<Applicant> chosenApplicants = {};
        chosenState() = default;
    };

    //number of positions to fill
    int positions = alist.size();
    //alist holds num positions and then inside vector of all applicants for each position

    //BASE CASE
    // IF no position to fill return 0
    if (positions == 0) return {0, {}};

    // Create a 2D vector to store the dynamic programming table
    //each cell contains a chosenState
    // Rows of table = position (+1 for base case)
    // Column of table = budget (each possible budget from 0 to budget)
    vector<vector<chosenState>> optimalSol(positions+1, vector<chosenState>(budget+1));

    // Build the table

    //from i up to positions (i starts at 1 because can't have 0 positions)
    for (int i = 1; i <= positions; i++) {

        //from j up to over each possible budget from 0 to maximum budget allowed
        for (int j = 0; j <= budget; j++) {

            //Assume the current state as the best state of the last position
            // Start by assuming the same budget, assuming no new aplicants are added at the position
            optimalSol[i][j].totalBenefit = optimalSol[i-1][j].totalBenefit;
            optimalSol[i][j].chosenApplicants = optimalSol[i-1][j].chosenApplicants;

            // Go over each applicant for the current position (i - 1 because 0 indexed)
            for (int k = 0; k < alist[i-1].size(); k++) {
                const Applicant& applicant = alist[i-1][k];  // Access the k-th applicant in the vector for position i-1

                //check if the current applicant being assessed is afordable with the budget j
                if (applicant.cost <= j) {
                    // if they are affordable check their potential benefit
                    float potentialBenefit = optimalSol[i-1][j-applicant.cost].totalBenefit + applicant.benefit;

                    //update the chosenState if this candidate is more beneficial
                    if (potentialBenefit > optimalSol[i][j].totalBenefit) {
                        optimalSol[i][j].totalBenefit = potentialBenefit;
                        optimalSol[i][j].chosenApplicants = optimalSol[i-1][j-applicant.cost].chosenApplicants;
                       optimalSol[i][j].chosenApplicants.push_back(applicant);
                    }
                }
            }
        }
    }

    // Retrieve the best choice of applicants
    vector<Applicant> bestApplicant = optimalSol[positions][budget].chosenApplicants;
    float optimalBenefit = optimalSol[positions][budget].totalBenefit;

    return {optimalBenefit, bestApplicant};
}


pair<int, vector<Applicant>> pickTeam_2(int budget, vector<vector<Applicant>>& alist) {

    // Define a structure to keep track of the total benefit and the list of chosen applicants at each state
    struct chosenState {
        float totalBenefit = 0.0;
        vector<Applicant> chosenApplicants = {};
        chosenState() = default;
    };

    // Get the number of positions available from the size of the applicant list vector
    int positions = alist.size();

    // If there are no positions available, return zero benefit and an empty vector of applicants
    if (positions == 0) return {0, {}};

    // Initialize table where each cell contains a chosenState object
    vector<vector<chosenState>> optimalSol(positions+1, vector<chosenState>(budget+1));

    // Iterate over each position
    for (int i = 1; i <= positions; i++) {
        // Iterate over each budget value from 0 to the maximum budget
        for (int j = 0; j <= budget; j++) {
            // Inherit the best solution from the previous position at the current budget
            optimalSol[i][j] = optimalSol[i-1][j];

            // Iterate over each applicant in the current position
            for (int k = 0; k < alist[i-1].size(); k++) {
                Applicant applicant1 = alist[i-1][k];

                // Check if the current applicant affordable on the current budget
                if (applicant1.cost <= j) {
                    // Calculate the new potential benefit if this applicant is chosen
                    float newBenefit = optimalSol[i-1][j-applicant1.cost].totalBenefit + applicant1.benefit;

                    // Update the state if this new benefit is greater than the current best for this budget
                    if (newBenefit > optimalSol[i][j].totalBenefit) {
                        optimalSol[i][j].totalBenefit = newBenefit;
                        optimalSol[i][j].chosenApplicants = optimalSol[i-1][j-applicant1.cost].chosenApplicants;
                        optimalSol[i][j].chosenApplicants.push_back(applicant1);
                    }
                }

                // Iterate over other applicants to check combinations of two applicants
                for (int l = k + 1; l < alist[i-1].size(); l++) {
                    Applicant applicant2 = alist[i-1][l];  // Access another applicant

                    // Calculate combined cost of the two applicants
                    int combinedCost = applicant1.cost + applicant2.cost;

                    // Check if the combined applicants can be afforded within the current budget
                    if (combinedCost <= j) {
                        // Calculate the new potential benefit if both applicants are chosen
                        float newBenefit = optimalSol[i-1][j-combinedCost].totalBenefit + applicant1.benefit + applicant2.benefit;////////

                        // Update the state if this new benefit is greater than the current best for this budget
                        if (newBenefit > optimalSol[i][j].totalBenefit) {
                            optimalSol[i][j].totalBenefit = newBenefit;
                            optimalSol[i][j].chosenApplicants = optimalSol[i-1][j-combinedCost].chosenApplicants;
                            optimalSol[i][j].chosenApplicants.push_back(applicant1);
                            optimalSol[i][j].chosenApplicants.push_back(applicant2);
                        }
                    }
                }
            }
        }
    }

    // Retrieve the best applicants and the highest total benefit from the last position at full budget
    vector<Applicant> bestApplicants = optimalSol[positions][budget].chosenApplicants;
    float optimalBenefit = optimalSol[positions][budget].totalBenefit;

    // Return the maximum benefit and the vector of chosen applicants as a pair
    return {optimalBenefit, bestApplicants};
}