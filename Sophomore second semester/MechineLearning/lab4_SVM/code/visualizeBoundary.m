function visualizeBoundary(X, y, model, varargin)

    plotData(X, y)
    
    % Make classification predictions over a grid of values
    x1plot = linspace(min(X(:,1)), max(X(:,1)), 1000)';
    x2plot = linspace(min(X(:,2)), max(X(:,2)), 1000)';
    [X1, X2] = meshgrid(x1plot, x2plot);
    vals = zeros(size(X1));
    for i = 1:size(X1, 2)
       this_X = [X1(:, i), X2(:, i)];
       vals(:, i) = svmPredict(model, this_X);
    end
    
    % Plot the SVM boundary
    hold on
    contour(X1, X2, vals, [0.5 0.5], 'b');
    hold off;

end
