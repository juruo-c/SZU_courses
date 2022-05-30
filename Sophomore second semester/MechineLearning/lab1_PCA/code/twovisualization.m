% input: matrix P(must be two dimensions) for reducing dimention, original matrix X
function twovisualization(P, X, Mean)
    Y = P * (X - repmat(Mean, 1, size(X, 2)));
    plot(Y(1, :), Y(2, :), "r*");
end