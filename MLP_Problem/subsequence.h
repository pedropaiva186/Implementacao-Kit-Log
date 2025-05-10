struct Subsequence {
    double T, C;
    int W;
    int first, last;
    
    inline static Subsequence Concatenate(Subsequence &sigma1, Subsequence &sigma2);
};

void updateAllSubseq(Solution &s, std::vector<std::vector<Subsequence>> &subseq_matriz);