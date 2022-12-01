from collections import Counter
import time
import sys


if __name__ == "__main__":
    count = 0
    word_counts = Counter()

    fileName = sys.argv[1]

    with open(fileName, 'r') as file:
        start_time = time.perf_counter()
        for line in file:
        # if count == 1000:
        #   break
            word_counts.update(line.split(' '))
            count += 1
        end_time = time.perf_counter()
    
    print(f'Top 5 most frequently occuring words - \n{word_counts.most_common(5)}')
    print(f'Top 5 least frequently occuring words - \n{word_counts.most_common()[:-5-1:-1]  }\n')


    print(f'Time taken = {end_time - start_time}')