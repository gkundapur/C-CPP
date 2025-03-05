class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<pair<int, int>> projects(n); //{capital, profits}
        for(int i = 0; i < n; i++)
            projects[i] = {capital[i], profits[i]};
        sort(projects.begin(), projects.end()); // sort based on capital

        int i = 0;
        priority_queue<int> pq; // add only profits
        while (k--) {
            while (i < n && projects[i].first <= w) {
                pq.push(projects[i].second);
                i++;
            }

            if (pq.empty())
                break;

            w += pq.top();
            pq.pop();
        }
        return w;        
    }
};
