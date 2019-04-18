./build/X86/gem5.opt --outdir=2bits-8K-bfs configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Local8KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/BFS_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/R10k.graph"

./build/X86/gem5.opt --outdir=2bits-8K-mst configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Local8KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/MST_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/rand-weighted-small.graph"

./build/X86/gem5.opt --outdir=2bits-8K-que configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Local8KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/queens_opt -o '-c 11'
#...
./build/X86/gem5.opt --outdir=2bits-32K-bfs configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Local32KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/BFS_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/R10k.graph"

./build/X86/gem5.opt --outdir=2bits-32K-mst configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Local32KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/MST_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/rand-weighted-small.graph"

./build/X86/gem5.opt --outdir=2bits-32K-que configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Local32KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/queens_opt -o '-c 11'
#...
./build/X86/gem5.opt --outdir=tour-8K-bfs configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Tournament8KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/BFS_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/R10k.graph"

./build/X86/gem5.opt --outdir=tour-8K-mst configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Tournament8KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/MST_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/rand-weighted-small.graph"

./build/X86/gem5.opt --outdir=tour-8K-que configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Tournament8KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/queens_opt -o '-c 11'
#...
./build/X86/gem5.opt --outdir=tour-32K-bfs configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Tournament32KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/BFS_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/R10k.graph"

./build/X86/gem5.opt --outdir=tour-32K-mst configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Tournament32KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/MST_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/rand-weighted-small.graph"

./build/X86/gem5.opt --outdir=tour-32K-que configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=Tournament32KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/queens_opt -o '-c 11'
#...
./build/X86/gem5.opt --outdir=gdac-8K-bfs configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=gDAC8KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/BFS_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/R10k.graph"

./build/X86/gem5.opt --outdir=gdac-8K-mst configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=gDAC8KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/MST_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/rand-weighted-small.graph"

./build/X86/gem5.opt --outdir=gdac-8K-que configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=gDAC8KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/queens_opt -o '-c 11'
#...
./build/X86/gem5.opt --outdir=gdac-32K-bfs configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=gDAC32KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/BFS_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/R10k.graph"

./build/X86/gem5.opt --outdir=gdac-32K-mst configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=gDAC32KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/MST_opt -o "/Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/inputs/rand-weighted-small.graph"

./build/X86/gem5.opt --outdir=gdac-32K-que configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache --bp-type=gDAC32KBP -c /Users/tobielf/Documents/ASU/CSE520/Assignment/benchmark/bin/queens_opt -o '-c 11'