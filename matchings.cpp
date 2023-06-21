#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> stableInternships(vector<vector<int>> interns, vector<vector<int>> teams)
{
  // keep track of matchings, all interns are initially unmatched
  vector<int> intern_matchings(interns.size(), -1);
  vector<int> teams_matchings(interns.size(), -1);

  // flag that there is an unmatched intern
  bool unmatched_intern = true;

  // keep trying to match while there is an unmatched intern
  while (unmatched_intern)
  {
    unmatched_intern = false;

    // go through intern i team preferences
    for (int i = 0; i < interns.size(); i++)
    {
      if (intern_matchings[i] != -1)
      {
        std::cout << "Intern " << i << " already matched with team "
                  << intern_matchings[i] << std::endl;
        continue;
      }

      // propose to each team j, in order of preference
      for (int j = 0; j < interns.size(); j++)
      {

        std::cout << "Intern " << i << " proposing to team " << j << ".\n";

        // team is available, match
        if (teams_matchings[j] == -1)
        {

          std::cout << "Team available, matched.\n";
          intern_matchings[i] = j;
          teams_matchings[j] = i;
          break;

          // team is currently matched, assert that proposition is interesting
        }
        else
        {

          // store potentially newly unassigned intern
          int assigned_intern = teams_matchings[j];

          std::cout << "Team already matched with intern " << assigned_intern
                    << ". Verifying rematch suitability.\n";

          // find out which intern is more attractive
          int proposing_intern_index = 0;
          int assigned_intern_index = 0;
          for (int k = 0; k < interns.size(); k++)
          {

            // fetch proposing intern index
            if (teams[j][k] == i)
            {
              proposing_intern_index = k;
            }
            if (teams[j][k] == assigned_intern)
            {
              assigned_intern_index = k;
            }
          }
          std::cout << "\t Proposing intern suitability: " << proposing_intern_index << std::endl;
          std::cout << "\t Assigned intern suitability: " << assigned_intern_index << std::endl;

          // proposer is more interesting, match
          if (proposing_intern_index < assigned_intern_index)
          {
            std::cout << "Proposer is more suitable, rematching.\n";
            intern_matchings[i] = j;
            teams_matchings[j] = i;
            intern_matchings[assigned_intern] = -1;
            unmatched_intern = true;
            break;
          }
          std::cout << "Proposer is less suitable, continue search.\n";
        }
      }
    }
  }

  vector<vector<int>> matches;
  for (int i = 0; i < intern_matchings.size(); i++)
  {
    matches.push_back({i, intern_matchings[i]});
  }
  return matches;
}