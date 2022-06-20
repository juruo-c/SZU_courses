clear;close all; clc

%% =========== Part 1: Recognize handwriting =============
% input_layer_size  = 400;  % 20x20 Input Images of Digits
% hidden_layer_size = 25;   % 25 hidden units
% num_labels = 10;          % 10 labels, from 1 to 10   
% 
% load('handwriting.mat');
% m = size(X, 1);
% 
% X_train = [];
% X_test = [];
% y_train = [];
% y_test = [];
% test_number = 0.3;
% for i = 500 : 500 : 5000
%     X_train = [X_train;X(i - 500 + 1 : i - 500 * test_number, :)];
%     y_train = [y_train;y(i - 500 + 1 : i - 500 * test_number, :)];
%     X_test = [X_test;X(i - 500 * test_number + 1 : i, :)];
%     y_test = [y_test;y(i - 500 * test_number + 1 : i, :)];
% end
% 
% % Initializing Pameters
% initial_Theta1 = randInitializeWeights(input_layer_size, hidden_layer_size);
% initial_Theta2 = randInitializeWeights(hidden_layer_size, num_labels);
% initial_nn_params = [initial_Theta1(:) ; initial_Theta2(:)];
% 
% % training 
% options = optimset('MaxIter', 350);
% lambda = 1;
% 
% % Create "short hand" for the cost function to be minimized
% costFunction = @(p) nnCostFunction(p, ...
%                                    input_layer_size, ...
%                                    hidden_layer_size, ...
%                                    num_labels, X_train, y_train, lambda);
% 
% % Now, costFunction is a function that takes in only one argument (the
% % neural network parameters)
% [nn_params, cost] = fmincg(costFunction, initial_nn_params, options);
% 
% % Obtain Theta1 and Theta2 back from nn_params
% Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
%                  hidden_layer_size, (input_layer_size + 1));
% 
% Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
%                  num_labels, (hidden_layer_size + 1));
% 
% % predict 
% pred = predict(Theta1, Theta2, X_test);
% fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred == y_test)) * 100);


%% =========== Part 2: PCA + NN ============= 

% orl
% address = 'D:\GradeTwoSemesterTwo\ML\data\ORL56_46\orl';
% suffix = '.bmp';
% Yale
address = 'D:\GradeTwoSemesterTwo\ML\data\face10080\subject';
suffix = '.bmp';
% FERET
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\FERET_80\ff';
% suffix = '.tif';
% AR
% address = 'D:\GradeTwoSemesterTwo\ML\data\AR_Gray_50by40\AR';
% suffix = '.tif';
class_cnt = 15;
train_cnt = 7;
eachclass_cnt = 11;

for PCA_components = 20 : 20 : 160
    [X_train, X_test, Label_train, Label_test, row, col] = Readdata(address, suffix, class_cnt, train_cnt, eachclass_cnt);
    model = PCA(X_train, PCA_components);
    
    X_train = model.W' * (X_train - repmat(model.miu, 1, size(X_train, 2)));
    X_test = model.W' * (X_test - repmat(model.miu, 1, size(X_test, 2)));
    
    input_layer_size  = PCA_components;  % Dimension of Input Images of Digits
    hidden_layer_size = 25;   % 25 hidden units
    num_labels = class_cnt;          % 10 labels, from 1 to 10   
    
    
    % Initializing Pameters
    initial_Theta1 = randInitializeWeights(input_layer_size, hidden_layer_size);
    initial_Theta2 = randInitializeWeights(hidden_layer_size, num_labels);
    initial_nn_params = [initial_Theta1(:) ; initial_Theta2(:)];
    
    % training 
    options = optimset('MaxIter', 10000);
    lambda = 1;
    
    % Create "short hand" for the cost function to be minimized
    costFunction = @(p) nnCostFunction(p, ...
                                       input_layer_size, ...
                                       hidden_layer_size, ...
                                       num_labels, X_train', Label_train', lambda);
    
    % Now, costFunction is a function that takes in only one argument (the
    % neural network parameters)
    [nn_params, cost] = fmincg(costFunction, initial_nn_params, options);
    
    % Obtain Theta1 and Theta2 back from nn_params
    Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                     hidden_layer_size, (input_layer_size + 1));
    
    Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                     num_labels, (hidden_layer_size + 1));
    
    % predict 
    pred = predict(Theta1, Theta2, X_test');
    fprintf('\n%d: Training Set Accuracy: %f\n',PCA_components, mean(double(pred == Label_test')) * 100);

end