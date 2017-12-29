#include "distance.h"

Distance::Distance()
{

}

//Distances

/*double jaro_distance(string str1, string str2) {
    int s1 = str1.size(), s2=str2.size();
    int maxSeparation = max(s1, s2)/2-1; //max(max(s1, s2)/2-1, 0);
    double transpositions = 0, match = 0;
    for (int i=0;i<s1;i++)
        for (int j=0;j<s2;j++)
            if (str1[i]==str2[j] && abs(i-j)<=maxSeparation)
                match+=1;
    transpositions = transpositions/2.; //Pas encore ça
    //cout << transpositions << endl;
    if (match==0)
        return 0;
    else
        return (match/double(s1) + match/double(s2) + (match-transpositions)/match)/3.;
}*/

double jaro_distance(const std::string s1, const std::string s2) {
    const uint l1 = s1.length(), l2 = s2.length();
    if (l1 == 0)
        return l2 == 0 ? 1.0 : 0.0;
    const uint match_distance = std::max(l1, l2) / 2 - 1;
    bool s1_matches[l1];
    bool s2_matches[l2];
    std::fill(s1_matches, s1_matches + l1, false);
    std::fill(s2_matches, s2_matches + l2, false);
    uint matches = 0;
    for (uint i = 0; i < l1; i++)
    {
        const int end = std::min(i + match_distance + 1, l2);
        for (int k = std::max(0u, i - match_distance); k < end; k++)
            if (!s2_matches[k] && s1[i] == s2[k])
            {
                s1_matches[i] = true;
                s2_matches[k] = true;
                matches++;
                break;
            }
    }
    if (matches == 0)
        return 0.0;
    double t = 0.0;
    uint k = 0;
    for (uint i = 0; i < l1; i++)
        if (s1_matches[i])
        {
            while (!s2_matches[k]) k++;
            if (s1[i] != s2[k]) t += 0.5;
            k++;
        }

    const double m = matches;
    return (m / l1 + m / l2 + (m - t) / m) / 3.0;
}

double jaro_winkler_distance(string str1, string str2, double coeff_winkler = 0.1) {
    double d_j = jaro_distance(str1, str2);
    int prefix = 0;
    while (prefix < min(str1.size(), str2.size()) && prefix < 4 && str1[prefix] == str2[prefix])
        prefix++;
    return (d_j + prefix * coeff_winkler * (1-d_j));
}

double levenshtein_distance(string str1, string str2) {
    int len1 = str1.size(), len2 = str2.size();
    vector<unsigned int> col(len2+1), prevCol(len2+1);

    for (unsigned int i = 0; i < prevCol.size(); i++)
        prevCol[i] = i;
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i+1;
        for (unsigned int j = 0; j < len2; j++)
                        // note that std::min({arg1, arg2, arg3}) works only in C++11,
                        // for C++98 use std::min(std::min(arg1, arg2), arg3)
            col[j+1] = min( min(prevCol[1 + j] + 1, col[j] + 1), prevCol[j] + (str1[i]==str2[j] ? 0 : 1) );
        col.swap(prevCol);
    }
    return prevCol[len2]; //Sans normalisation
}

double DTW(vector<double> v1, vector<double> v2) {
    int s1 = v1.size(), s2=v2.size();
    double* dtw = new double[(s1+1)*(s2+1)];
    dtw[0]=0;
    for (unsigned int i = 1; i < s1+1; i++)
        dtw[i*(s2+1)+0]=1;
    for (unsigned int j = 1; j < s2+1; j++)
        dtw[0*(s2+1)+j]=1;

    for (unsigned int i = 0; i < s1; i++)
        for (unsigned int j = 0; j < s2; j++)
            dtw[(i+1)*(s2+1)+(j+1)] = abs(v1[i]-v1[j]) + min(min(dtw[i*(s2+1)+(j+1)], dtw[(i+1)*(s2+1)+j]), dtw[i*(s2+1)+j]);

    return dtw[s1*(s2+1)+s2];
}
