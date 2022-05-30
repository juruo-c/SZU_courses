function [X_train, X_test, Label_train, Label_test] = MLRC_ReadandPre(address, suffix, class_cnt, train_cnt, eachclass_cnt, image_row, image_col, n, m)
    % Inputs: -address: data address
    %         -suffix: data's suffix
    %         -class_cnt: the number of classes, 
    %         -train_cnt: count of datas for training in each class
    %         -eachclass_cnt: count of the datas in each class
    %         -image_row: the row of original image
    %         -image_col: the col of original image
    %         -n: the divisions of row
    %         -m: the divisions of col
    % Outputs: -X_train: matrix of the training set of each modural(as column vector)
    %          -X_test: matrix of the testing set of each modural
    %          -Label_train: labels of training set of each modural
    %          -Label test: labels of testing set 
    % Author: Yang Zheng
    % Date: 2022. 4. 6
    X_train = zeros(image_row * image_col / n / m, train_cnt, n * m);
    X_test = zeros(image_row * image_col / n / m, train_cnt, n * m); 
    Label_train = zeros(1, train_cnt * class_cnt, n * m); 
    Label_test = zeros(1, (eachclass_cnt - train_cnt) * class_cnt, n * m);
    row = image_row / n;
    col = image_col / m;
    %% read data
    for i = 1 : class_cnt
        for j = 1 : eachclass_cnt
            % ORL and FERET
%             tmp_img = imread(strcat(address, num2str(i), '_', num2str(j), suffix));
%             % Yale
%             if (i < 10)
%                 tmp_img = imread(strcat(address, '0', num2str(i), '_', num2str(j), suffix));
%             else
%                 tmp_img = imread(strcat(address, num2str(i), '_', num2str(j), suffix));
%             end
            % AR
            if (i < 10)
                tmp_img = imread(strcat(address, '00', num2str(i), '-', num2str(j), suffix));
            else 
                if(i < 100)
                    tmp_img = imread(strcat(address, '0', num2str(i), '-', num2str(j), suffix));
                else
                    tmp_img = imread(strcat(address, num2str(i), '-', num2str(j), suffix));
                end
            end
            
            for k = 1 : n
                for p = 1 : m
                    rl = 1 + row * (k - 1);
                    rr = rl + row - 1;
                    cl = 1 + col * (p - 1);
                    cr = cl + col - 1;
                    X_tmp = tmp_img(rl : rr, cl : cr);
                    X_tmp = reshape(X_tmp, row * col, 1);
                    if (j <= train_cnt)
                        X_train(:, j + (i - 1) * train_cnt, (k - 1) * n + p) = X_tmp;
                        Label_train(1, j + (i - 1) * train_cnt, (k - 1) * n + p) = i;
                    else 
                        X_test(:, j - train_cnt + (i - 1) * (eachclass_cnt - train_cnt), (k - 1) * n + p) = X_tmp;
                        Label_test(1, j - train_cnt + (i - 1) * (eachclass_cnt - train_cnt), (k - 1) * n + p) = i;
                    end
                end
            end
        end
    end
end