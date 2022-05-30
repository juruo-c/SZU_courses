function model = LDA(X_train, Label_train, components)
    % Inputs:
    %       -X_train: training set, [dimension x data_num]
    %       -Label_train: labels of training set, [1 x data_num]
    %       -components: number of components to keep, [int]
    % Outputs:
    %       -model:
    %           model.components: number of components in this model, [int]
    %           model.W: the matrix for projection by LDA, [dimension x components]
    % Author: Yang Zheng
    % Date: 2022. 3. 24
    
    %% initialize
    [dimension, ~] = size(X_train);
    class_num = max(Label_train);
    components = min(components, class_num - 1);

    %% calculate the total mean vector
    meantot = mean(X_train, 2);

    %% calculate Sw and Sb
    Sw = zeros(dimension, dimension);
    Sb = zeros(dimension, dimension);
    for i = 1 : class_num
        Xi = X_train(:, find(Label_train == i));
        meani = mean(Xi, 2);
        Xi = Xi - repmat(meani, 1, size(Xi, 2));
        Sw = Sw + Xi * Xi';
        Sb = Sb + size(Xi, 2) * (meani - meantot) * (meani - meantot)';
    end

    %% calculate the eigenvectors and sort them with the eigen values descend
    [V, D] = eig(Sb, Sw);
    [~, I] = sort(diag(D), 1, 'descend');
    V = V(:, I);

    %% build model
    model.components = components;
    model.W = V(:, 1 : components);
end