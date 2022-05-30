function TwoandThreedimension(X_train, Label_train, X_test, Label_test, class_cnt, row, col)
    %% Two dimension visualization
%     k = 2;
%     % PCA
%     [V, Mean] = PCA(X_train);
%     P = [];
%     for i = size(V, 1) : -1 : (size(V, 1) - k + 1) % because the eigenvalues with descending order
%         P = [P; V(i, :)];
%     end
%     [~, siz] = size(X_test);
%     figure(1)
%     for i = 1 : siz
%         subplot(3, 3, i);
%         imshow(reshape(X_test(:, i), row, col), []);
%     end
%     Y_test = P * (X_test - repmat(Mean, 1, siz));
%     sz = [];
%     for i = 1 : siz
%         sz(i) = i * 40;
%     end
%     % scatter the point after dimension
%     figure(2)
%     scatter(Y_test(1, :), Y_test(2, :), 25, Label_test, "filled");
% 
%     %LDA
%     [W, D] = Multi_Class_LDA(X_train, Label_train, class_cnt);
%     [~,I] = sort(diag(D), "descend");
%     W = W(:, I(1 : k))';
%     Y_test = W * X_test;
%     % scatter the point after dimension
%     figure(3)
%     scatter(Y_test(1, :), Y_test(2, :), 25, Label_test, "filled");
    %% Three dimension visualization 
    k = 3;
    % PCA
    [V, Mean] = PCA(X_train);
    P = [];
    for i = size(V, 1) : -1 : (size(V, 1) - k + 1) % because the eigenvalues with descending order
        P = [P; V(i, :)];
    end
    [~, siz] = size(X_test);
    Y_test = P * (X_test - repmat(Mean, 1, siz));
    sz = [];
    for i = 1 : siz
        sz(i) = i * 40;
    end
    % scatter the point after dimension
    figure(1)
    scatter3(Y_test(1, :), Y_test(2, :), Y_test(3, :), 25, Label_test, "filled");

    %LDA
    [W, D] = Multi_Class_LDA(X_train, Label_train, class_cnt);
    [~,I] = sort(diag(D), "descend");
    W = W(:, I(1 : k))';
    Y_test = W * X_test;
    % scatter the point after dimension
    figure(2)
    scatter3(Y_test(1, :), Y_test(2, :), Y_test(3, :), 25, Label_test, "filled");
end