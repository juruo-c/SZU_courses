function eigenfaceandfisherface(X_train, Label_train, class_cnt, row, col)
    PCA_k = 100;
    LDA_k = 39;
    %% first k eigenface 
    [V, Mean] = PCA(X_train);
    % get the eigenface matrix 
    P = [];
    for i = size(V, 1) : -1 : (size(V, 1) - PCA_k + 1) % because the eigenvalues with descending order
        P = [P; V(i, :)];
    end
    [~, siz] = size(X_train);
    Y_train = P * (X_train - repmat(Mean, 1, siz));

    % show the eigenface
    P = P';
    figure(1);
    for i = 1 : 20
        subplot(4, 5, i);
        imshow(reshape(P(:, i), row, col), []);
    end
    %% first k fisherface
    [W, D] = Multi_Class_LDA(Y_train, Label_train, class_cnt);
    % get the fisherface matrix
    [~,I] = sort(diag(D), "descend");
    W = W(:, I(1 : LDA_k));
    W = P * W;
    % show the fisherface
    figure(2);
    for i = 1 : 20
        subplot(4, 5, i);
        imshow(reshape(W(:, i), row, col), []);
    end
    
end