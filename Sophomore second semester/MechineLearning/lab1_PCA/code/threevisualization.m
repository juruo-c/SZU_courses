% input: matrix P(must be three dimentions) for reducing dimention, original matrix X
function threevisualization(P, X, Mean)
    Y = P * (X - repmat(Mean, 1, size(X, 2)));
    plot3(Y(1, :), Y(2, :), Y(3, :), "r*");
end