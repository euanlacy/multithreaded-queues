from math import sqrt

def process_all(file, dictionary):
    # skip header
    for _ in range(3):
        next(file)

    for _ in file:
        sfqueue = next(file).rstrip()[-3:]
        dictionary.setdefault("SFQueue", []).append(sfqueue)
        next(file)

        next(file)
        lcqueue = next(file).rstrip()[-4:]
        dictionary.setdefault("LCQueue", []).append(lcqueue)
        next(file)

        next(file)
        cqueue = next(file).rstrip()[-4:]
        dictionary.setdefault("CQueue", []).append(cqueue)
        next(file)

        next(file)
        fqueue = next(file).rstrip()[-4:]
        dictionary.setdefault("FQueue", []).append(fqueue)
        next(file)

        next(file)
        lfqueue = next(file).rstrip()[-4:]
        dictionary.setdefault("LFQueue", []).append(lfqueue)
        next(file)
        break

def process_thread_safe(file, dictionary):
    # skip header
    for _ in range(3):
        next(file)

    for _ in file:
        cqueue = next(file).rstrip()[5:]
        dictionary.setdefault("CQueue", []).append(cqueue)
        next(file)

        next(file)
        lcqueue = next(file).rstrip()[5:]
        dictionary.setdefault("LCQueue", []).append(lcqueue)
        next(file)

        next(file)
        fqueue = next(file).rstrip()[5:]
        dictionary.setdefault("FQueue", []).append(fqueue)
        next(file)

        next(file)
        lfqueue = next(file).rstrip()[5:]
        dictionary.setdefault("LFQueue", []).append(lfqueue)
        next(file)
        break

enqueue = {}
dequeue = {}

one_one = {}
five_one = {}
one_five = {}
two_two = {}
three_three = {}

for i in range(1, 11):
    with open(f"run-{i}", "r") as file:
        process_all(file, enqueue)
        process_all(file, dequeue)

        process_thread_safe(file, one_one)
        process_thread_safe(file, five_one)
        process_thread_safe(file, one_five)
        process_thread_safe(file, two_two)
        process_thread_safe(file, three_three)
        

# print(enqueue)
# print(dequeue)
# print(one_one)
# print(five_one)
# print(one_five)
# print(two_two)
# print(three_three)

def process_list(strings: list[str]):
    nums = [int(string[:-2]) for string in strings]
    mean = sum(nums) / len(nums)
    std_dev = sqrt(sum([(x - mean) ** 2 for x in nums])/len(nums))

    return mean, std_dev

def get_average(dictionary):
    return { k: process_list(v) for k, v in dictionary.items()}

print("Enqueue: ", get_average(enqueue))
print("Dequeue: ",get_average(dequeue))
print("one-one: ",get_average(one_one))
print("five-one: ",get_average(five_one))
print("one-five: ",get_average(one_five))
print("two-two: ",get_average(two_two))
print("three-three: ",get_average(three_three))
