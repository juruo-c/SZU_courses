% input: data address, count of classes, 
%        count of datas for training, count of the datas in each class
% output: matrix of the training set(as column vector), matrix of the testing set,
%         labels of training set, labels of testing set, 
%         row of original image, column of original image
function [X_train, X_test, Label_train, Label_test, row, col] = Read_data(address, suffix, class_cnt, train_cnt, eachclass_cnt)
    X_train = [];X_test = []; Label_train = []; Label_test = [];
    %% read data
    train_num = 0;
    test_num = 0;
    for i = 1 : class_cnt
        for j = 1 : eachclass_cnt
            tmp_img = imread(strcat(address, num2str(i), '_', num2str(j), suffix));
            [row, col] = size(tmp_img);
            tmp_img = reshape(tmp_img, row * col, 1);
            tmp_img = double(tmp_img);
            if (j <= train_cnt)
                X_train = [X_train tmp_img];
                train_num = train_num + 1;
                Label_train(1, train_num) = i;
            else
                X_test = [X_test tmp_img];
                test_num = test_num + 1;
                Label_test(1, test_num) = i;
            end
        end
    end
end