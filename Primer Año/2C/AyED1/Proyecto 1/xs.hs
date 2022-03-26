h :: [Int] -> Bool
h [] = False
h (x:xs) = hGen (x-1) xs

hGen :: Int -> [Int] -> Bool
hGen _ [] = False
hGen 0 xs = h xs
hGen n (x:xs) = n > 0 || hGen (2*n) xs


----------------------------------------


f :: [Int] -> Bool
f [] = True
f (x:xs) = fGen (x-1) xs

fGen :: Int -> [Int] -> Bool
fGen n [] = n /= 1
fGen n (x:xs) = fGen (2*n) xs && n /= 1