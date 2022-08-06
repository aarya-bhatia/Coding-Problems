#include <vector>
#include <iostream>

struct Range
{
    int start;
    int end;
    int sum;

    Range(int start, int end, int sum): start(start), end(end), sum(sum)
    {
    }
};

struct SubMatrix
{
    int rowStart;
    int colStart;
    int rowEnd;
    int colEnd;
    int sum;

    SubMatrix(int rowStart, int colStart, int rowEnd, int colEnd, int sum):
        rowStart(rowStart),
        colStart(colStart),
        rowEnd(rowEnd),
        colEnd(colEnd),
        sum(sum)
    {
    }

    void print() const
    {
        std::cout << rowStart
        << "," << colStart << ","
        << rowEnd << "," 
        << colEnd << ": " << sum 
        << "\n";
    }
};

// O(n)
Range getMaxSubArray(int *array, int n)
{
    int sum = 0;
    int start = 0;
    Range best(0,0,-1);

    for(int i = 0; i < n; i++)
    {
        sum += array[i];

        if(best.sum == -1 || best.sum < sum) 
        {
            best = Range(start, i, sum);
        }

        if(sum < 0)
        {
            start = i+1;
            sum = 0;
        }
    }

    return best;
}

// O(n^3) time, O(n) space
SubMatrix getMaxMatrix(const std::vector<std::vector<int> > &matrix)
{
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    SubMatrix best(0,0,0,0,-1);

    for(int rowStart = 0; rowStart < numRows; rowStart++)
    {
        int partialSum[numCols]; // store column sums from rowStart to rowEnd

        for(int i = 0; i < numCols; i++) partialSum[i] = 0;

        for(int rowEnd = rowStart; rowEnd < numRows; rowEnd++)
        {
            for(int col = 0; col < numCols; col++) {
                partialSum[col] += matrix[rowEnd][col];
            }

            // get col start and end point for max sum 
            // for the submatrix with current row start and row end point
            Range bestRange = getMaxSubArray(partialSum, numCols);

            if(best.sum == -1 || best.sum < bestRange.sum) 
            {
                best = SubMatrix(rowStart, bestRange.start, rowEnd, bestRange.end, bestRange.sum);
                std::cout << "New max subarray: "; 
                best.print();
            }
        }
    }

    return best;
}
 
int main()
{
    std::vector<std::vector<int> > matrix = {
        { 1, 5, -1, 2 },
        { 4, -2, 0, 6 },
        { 8, -5, 2, 1 },
        { -4, 7, -2, -2 }
    };

    SubMatrix subMat = getMaxMatrix(matrix);

    for(int r = subMat.rowStart; r <= subMat.rowEnd; r++)
    {
        for(int c = subMat.colStart; c <= subMat.colEnd; c++)
        {
            std::cout << matrix[r][c] << " ";        
        }
        std::cout << "\n";
    }

    std::cout << "Sum: " << subMat.sum << "\n";
}