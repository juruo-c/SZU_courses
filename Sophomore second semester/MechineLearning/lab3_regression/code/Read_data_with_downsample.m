% Inputs: -address: data address
%         -suffix: data's suffix
%         -class_cnt: the number of classes, 
%         -train_cnt: count of datas for training in each class
%         -eachclass_cnt: count of the datas in each class
%         -n, m: the dimension of downsampled matrix
% Outputs: -X_train: matrix of the training set(as column vector)
%          -X_test: matrix of the testing set
%          -Label_train: labels of training set
%          -Label test: labels of testing set 
%          -row: row of original image 
%          -col: column of original image
% Author: Yang Zheng
% date: 2022. 4. 4
function [X_train, X_test, Label_train, Label_test] = Read_data_with_downsample(address, suffix, class_cnt, train_cnt, eachclass_cnt, n, m)
    X_train = [];
    X_test = []; 
    Label_train = []; 
    Label_test = [];
    %% read data
    train_num = 0;
    test_num = 0;
    for i = 1 : class_cnt
        for j = 1 : eachclass_cnt
            % ORL and FERET
            tmp_img = imread(strcat(address, num2str(i), '_', num2str(j), suffix));
%             % Yale
%             if (i < 10)
%                 tmp_img = imread(strcat(address, '0', num2str(i), '_', num2str(j), suffix));
%             else
%                 tmp_img = imread(strcat(address, num2str(i), '_', num2str(j), suffix));
%             end
            % AR
%             if (i < 10)
%                 tmp_img = imread(strcat(address, '00', num2str(i), '-', num2str(j), suffix));
%             else 
%                 if(i < 100)
%                     tmp_img = imread(strcat(address, '0', num2str(i), '-', num2str(j), suffix));
%                 else
%                     tmp_img = imread(strcat(address, num2str(i), '-', num2str(j), suffix));
%                 end
%             end
            tmp_img = downsample(tmp_img, n, m);
            tmp_img = reshape(tmp_img, n * m, 1);
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