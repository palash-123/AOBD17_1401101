clear all;
%The following code runs for 1000 iterations and splits the data matrix of
%the input image into a low-rank matrix and sparse matrix.
X = im2double(imread('image1.jpg'));
X = X(:,:,1);
[L, S] = RobustPCA(X);
subplot(1,3,1);
imshow(X);
subplot(1,3,2);
imshow(L);
subplot(1,3,3);
imshow(S);