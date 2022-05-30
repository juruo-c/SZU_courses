% input: the matrix for reducing dimension, testing set,
%        the row of original image, the column of original image,
%        the mean vector of training set
function rebuild(P, X_test, r, c, Mean)
    [~, col] = size(X_test);
    Y = P * (X_test - repmat(Mean, 1, col));
    X = P' * Y;
    %% show the rebuilded face
    figure(1);
    for i = 1 : col
        img = X(:, i) + Mean;
        img = reshape(img, r, c);
        subplot(2, 5, i);
        imshow(img, []);
    end
    %% show the original face
    figure(2);
    for i = 1 : col
        img = X_test(:, i);
        img = reshape(img, r, c);
        subplot(2, 5, i);
        imshow(img, []);
    end
end