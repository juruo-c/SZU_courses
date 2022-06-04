function model = PCA(X_train, components)
    % Inputs:
    %       -X_train: training set, [dimension x data_num]
    %       -components: number of components to keep, [int]
    % Outputs:
    %       -model:
    %           model.components: number of components in this model, [int]
    %           model.W: the matrix for projection by PCA, [dimension x components]
    %           model.miu: the mean vector of X_train, [dimension x 1]
    % Author: Yang Zheng
    % Date: 2022. 3. 24

    %% PCA by svd
    miu = mean(X_train, 2);
    X_train = X_train - repmat(miu, 1, size(X_train, 2));
    [E, D, V] = svd(X_train, 'econ');

    %% build model
    model.components = components;
    model.W = E(:, 1 : components);
    model.miu = miu;
end