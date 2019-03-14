./build/X86/gem5.opt --outdir=256-bfs-lru1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_rMatGraph_J_5_90000

./build/X86/gem5.opt --outdir=256-bfs-lru2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_randLocalGraph_J_5_120000

./build/X86/gem5.opt --outdir=256-mst-lru1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_rMatGraph_WE_5_35000

./build/X86/gem5.opt --outdir=256-mst-lru2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_randLocalGraph_WE_5_100000

./build/X86/gem5.opt --outdir=256-bfs-srrip1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_rMatGraph_J_5_90000

./build/X86/gem5.opt --outdir=256-bfs-srrip2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_randLocalGraph_J_5_120000

./build/X86/gem5.opt --outdir=256-mst-srrip1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_rMatGraph_WE_5_35000

./build/X86/gem5.opt --outdir=256-mst-srrip2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_randLocalGraph_WE_5_100000

./build/X86/gem5.opt --outdir=256-bfs-ship1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_rMatGraph_J_5_90000

./build/X86/gem5.opt --outdir=256-bfs-ship2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_randLocalGraph_J_5_120000

./build/X86/gem5.opt --outdir=256-mst-ship1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_rMatGraph_WE_5_35000

./build/X86/gem5.opt --outdir=256-mst-ship2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=256kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_randLocalGraph_WE_5_100000

./build/X86/gem5.opt --outdir=1024-bfs-lru1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_rMatGraph_J_5_90000

./build/X86/gem5.opt --outdir=1024-bfs-lru2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_randLocalGraph_J_5_120000

./build/X86/gem5.opt --outdir=1024-mst-lru1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_rMatGraph_WE_5_35000

./build/X86/gem5.opt --outdir=1024-mst-lru2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_randLocalGraph_WE_5_100000

./build/X86/gem5.opt --outdir=1024-bfs-srrip1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_rMatGraph_J_5_90000

./build/X86/gem5.opt --outdir=1024-bfs-srrip2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_randLocalGraph_J_5_120000

./build/X86/gem5.opt --outdir=1024-mst-srrip1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_rMatGraph_WE_5_35000

./build/X86/gem5.opt --outdir=1024-mst-srrip2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_randLocalGraph_WE_5_100000

./build/X86/gem5.opt --outdir=1024-bfs-ship1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_rMatGraph_J_5_90000

./build/X86/gem5.opt --outdir=1024-bfs-ship2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_randLocalGraph_J_5_120000

./build/X86/gem5.opt --outdir=1024-mst-ship1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_rMatGraph_WE_5_35000

./build/X86/gem5.opt --outdir=1024-mst-ship2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=1024kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_randLocalGraph_WE_5_100000

./build/X86/gem5.opt --outdir=4096-bfs-lru1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_rMatGraph_J_5_90000

./build/X86/gem5.opt --outdir=4096-bfs-lru2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_randLocalGraph_J_5_120000

./build/X86/gem5.opt --outdir=4096-mst-lru1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_rMatGraph_WE_5_35000

./build/X86/gem5.opt --outdir=4096-mst-lru2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=LRURP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_randLocalGraph_WE_5_100000

./build/X86/gem5.opt --outdir=4096-bfs-srrip1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_rMatGraph_J_5_90000

./build/X86/gem5.opt --outdir=4096-bfs-srrip2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_randLocalGraph_J_5_120000

./build/X86/gem5.opt --outdir=4096-mst-srrip1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_rMatGraph_WE_5_35000

./build/X86/gem5.opt --outdir=4096-mst-srrip2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=SRRIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_randLocalGraph_WE_5_100000

./build/X86/gem5.opt --outdir=4096-bfs-ship1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_rMatGraph_J_5_90000

./build/X86/gem5.opt --outdir=4096-bfs-ship2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/BFS_opt -o ../assignment/benchmark_assign2/BFS_randLocalGraph_J_5_120000

./build/X86/gem5.opt --outdir=4096-mst-ship1 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_rMatGraph_WE_5_35000

./build/X86/gem5.opt --outdir=4096-mst-ship2 configs/example/se.py --cpu-type=AtomicSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=4096kB '--l2_rpp=SHIPRP()' -c ../assignment/benchmark/bin/MST_opt -o ../assignment/benchmark_assign2/MST_randLocalGraph_WE_5_100000
