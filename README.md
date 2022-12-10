# CSC 746 Project - Parallelization of Text Processing Algorithms

## Requirements

- Project Files
- CMake
- GNU Compiler
- Dataset Files

## Downloading the Project Files

The project is available on Github and can be downloaded using the following command

```bash
git clone https://github.com/sanketnaik99/CSC746_Project.git
```

## How to download dataset files

Please download the dataset files from this box link - [Box Drive Link](https://sfsu.box.com/s/cmq2vc6e1rlocxz81ha8dx2w8bd826ts)

### Steps to set up the data

- Please download all dataset files from the box drive link
- create a new directory in the project folder by entering the following command

  ```bash
  mkdir data
  ```

- You can upload the dataset files in the data folder using the [NERSC File Browser](https://my.nersc.gov/filebrowser.php)
- Kindly make sure that all dataset files are arranged as follows

  ```bash
  .
  └── <project_root_folder>/
      └── data/
          ├── 10k-dataset.txt
          ├── 100k-dataset.txt
          ├── 1M-dataset.txt
          └── 2M-dataset.txt
  ```

# Building and Running the Program

All programs should run on a CORI KNL nodes. The directions for running the program are as follows -

## Load Required Modules

```bash
module load cmake
module swap PrgEnv-intel PrgEnv-gnu
```

## Request a CORI KNL Node in Interactive Mode

```bash
salloc --nodes 1 --qos interactive --time 01:00:00 --constraint knl --account m3930
```

## Build and Make the app

```bash
mkdir build
cd build
cmake ../
make
```

## Run the Program

```bash
# make the job bash script an executable
chmod +x ./job-openmp

# Run the job - this will run the program on all 4 datasets and all concurrency levels
./job-openmp
```

### Running using dynamic thread scheduling

To run the program using dynamic thread scheduling, modify the `job.in` file as follows

```bash
# Comment out this line
# export OMP_SCHEDULE=static

# Uncomment this line
export OMP_SCHEDULE=dynamic
```

Build and run the app again to verify the dynamic thread scheduling results.

> **Note**: If the execution takes longer than 200 seconds, please stop the execution by pressing `CTRL+C`. This is because sometimes the program may run into an infinite loop due to an unknown bug.

## Running the python program

To run the python program, navigate out of the build directoy and run the script and provide the desired dataset as the second argument as follows

```bash
# Navigate out of the build directory
cd ../

# Run Python Script on different datasets
python3 count_words.py data/10k-dataset.txt
python3 count_words.py data/100k-dataset.txt
python3 count_words.py data/1M-dataset.txt
python3 count_words.py data/2M-dataset.txt
```
