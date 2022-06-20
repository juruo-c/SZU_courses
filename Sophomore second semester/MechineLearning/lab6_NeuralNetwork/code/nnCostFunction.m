function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%
% ori = X;
% X = [ones(m, 1) X];
% X = sigmoid(Theta1 * X');
% X = [ones(1, m); X];
% X = sigmoid(Theta2 * X);
% Y = zeros(num_labels, m);
% for i = 1 : m
%     Y(y(i), i) = 1;
% end
% 
% temp = (-Y .* log(X)) - ((1 - Y) .* log(1 - X));
% J = sum(temp(:)) / m;
% 
% temp1 = Theta1.^2;
% temp2 = Theta2.^2;
% temp1 = temp1(:, 2 : size(temp1, 2));
% temp2 = temp2(:, 2 : size(temp2, 2));
% J = J + lambda * (sum(temp1(:)) + sum(temp2(:))) / 2 / m;
% 
% X = ori;
% Delta1 = zeros(size(Theta1));
% Delta2 = zeros(size(Theta2));
% for i = 1 : m
%     a1 = X(i, :)';
%     a1 = [1; a1];
%     z2 = Theta1 * a1;
%     a2 = sigmoid(z2);
%     a2 = [1; a2];
%     z3 = Theta2 * a2;
%     a3 = sigmoid(z3);
%     yi = zeros(num_labels, 1);
%     yi(y(i)) = 1;
%     delta3 = a3 - yi;
%     delta2 = Theta2(:, 2 : end)' * delta3 .* sigmoidGradient(z2);
%     Delta1 = Delta1 + delta2 * a1';
%     Delta2 = Delta2 + delta3 * a2';
% end
% temp1 = Theta1(:, 2 : end);
% temp2 = Theta2(:, 2 : end);
% temp1 = [zeros(size(temp1, 1), 1) temp1];
% temp2 = [zeros(size(temp2, 1), 1) temp2];
% Delta1 = Delta1 / m + lambda * temp1 / m;
% Delta2 = Delta2 / m + lambda * temp2 / m;
% 
% Theta1_grad = Delta1;
% Theta2_grad = Delta2;
% 
% 
% 
% 

%
a1 = [ones(m,1) X];
z2 = a1 * Theta1';
a2 = [ones(m,1) sigmoid(z2)];
z3 = a2 * Theta2';
a3 = sigmoid(z3);
yv = (1 : num_labels) == y;
%计算损失函数
J = (1/m) * sum(sum(-yv .* log(a3) - (1 - yv) .* log(1-a3))) ... 
+(lambda/(2 * m)) * (sum(sum(Theta1 .^ 2)) + sum(sum(Theta2.^2)) ... 
- sum(Theta1(:,1).^2) -sum(Theta2(:,1).^2));
d3 = a3 - yv;
d2 = d3 * Theta2(:,2:end) .* sigmoidGradient(z2);
D1 = d2' * a1;
D2 = d3' * a2;
% 计算两层神经元的权重和偏置的梯度
Theta1_grad = D1/m + (lambda/m) * Theta1;
Theta1_grad(:,1) = Theta1_grad(:,1)-(lambda/m) * Theta1(:,1);
Theta2_grad = D2/m + (lambda/m) * Theta2;
Theta2_grad(:,1) = Theta2_grad(:,1) - (lambda/m) * Theta2(:,1);


% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
