# to help you evaluate this project, 
# you can execute the following commands 
# to compare results from ft containers 
# with results from stl containers

check map validity and display with :

```sh
CHECK_STATUS="1" make re -j 
```

compare results with :

```sh

time ./ft_containers_FT 1 > ft_results
time ./ft_containers_STL 1 > stl_results
diff ft_results stl_results
```