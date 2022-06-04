function [centroids, idx] = kmeans(X, k, plot_progress)
% Set default value for plot progress
if ~exist('plot_progress', 'var') || isempty(plot_progress)
    plot_progress = false;
end

% Plot the data if we are plotting progress
if plot_progress
    figure;
    hold on;
end

randidx = randperm(size(X, 1));
initial_centroids = X(randidx(1:k), :);

% Initialize values
[m n] = size(X);
centroids = initial_centroids;
previous_centroids = centroids;
idx = zeros(m, 1);
cnt = 0;

while(true)
    cnt = cnt + 1;

    if exist('OCTAVE_VERSION')
        fflush(stdout);
    end
    
    % compute r for each sample
    idx = zeros(m, 1);
    for i = 1 : m
        dist = zeros(k, 1);
        Xi = X(i, :);
        for j = 1 : k
            dist(j) = sum((Xi - centroids(j, :)).^2);
        end
        [~, index] = sort(dist, 'ascend');
        idx(i) = index(1);
    end
    
    if plot_progress
        plotProgresskMeans(X, centroids, previous_centroids, idx, k, cnt);
        previous_centroids = centroids;
        fprintf('Press enter to continue.\n');
        pause;
    end
    
    % compute new centroids
    for i = 1 : k
        Xi = X(idx == i, :);
        miu = mean(Xi, 1);
        centroids(i, :) = miu;
    end

    if (centroids == previous_centroids)
        break;
    end
end

% Hold off if we are plotting progress
if plot_progress
    hold off;
end

end

