import subprocess

executable_path = './a.out'

# no. of times to run the executable
num_runs = 10

time_taken_values = []
gflops_values = []

for _ in range(num_runs):
    result = subprocess.run([executable_path], capture_output=True, text=True)
    output_lines = result.stdout.strip().split('\n')
    
    time_taken = float(output_lines[0].split(': ')[1].split()[0])
    gflops = float(output_lines[1].split(': ')[1])
    
    time_taken_values.append(time_taken)
    gflops_values.append(gflops)

average_time_taken = sum(time_taken_values) / len(time_taken_values)
average_gflops = sum(gflops_values) / len(gflops_values)

print(f'Average Time taken over {num_runs} runs: {average_time_taken} seconds')
print(f'Average GFLOPS over {num_runs} runs: {average_gflops}')
