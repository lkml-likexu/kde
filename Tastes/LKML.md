前沿技术选题 (内核社区)

> 说明（2026-09-24 自动补充）：
> 1. 已为每个 lore.kernel.org 链接补充一段中文概述（较早缺失的 60 条为 ≤100 字精简概述，其余为原有详解）。
> 2. 每条补丁集追加「主线状态」行，HEAD = v7.3-rc4，2026-09-23：
>    - ✅ 已进入 mainline：通过 commit 中的 `Link:` message-id 匹配、或作者+提交标题强匹配确认，并尽量给出合入版本与对应改动示例；
>    - ⚠️ 曾合入后被回退（revert）；
>    - ❔ 未自动检索到合入记录：**并不等于未合入**——文档常链接早期版本（RFC/v1），而合入的多为改版；此类需人工确认。
> 3. 自动判定为高精度但低召回（确认合入 96 条），存在漏判；如需对某条深入核实可单独指出。

## 2026年 第09期 (Start From 2026/09/01)

#### arm64: entry: Convert to Generic Entry
- https://lore.kernel.org/all/20260922035510.1090299-1-ruanjinjie@huawei.com/
- 本补丁系列（v19，共14个补丁）将 arm64 架构迁移到通用入口（Generic Entry）框架。继此前已采用通用 IRQ 入口后，此次转换使 arm64 与 x86、RISC-V、LoongArch、PowerPC、s390 等架构保持一致，减少重复代码、降低维护成本，并为 Syscall User Dispatch、rseq 时间片扩展等特性优化奠定基础。代码基于 v7.3-rc4，已通过 stress-ng、hackbench、多项 kselftest、ptrace 压力测试及伪 NMI 负载测试验证。在 gVisor systrap 模式下，SUD 特性使 arm64 获得约 3%~5% 的性能提升（100 万次 getpid 平均耗时），与 x86 表现相近。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Allow AET to use PMT as loadable module
- https://lore.kernel.org/all/20260916231320.14502-1-tony.luck@intel.com
- 本补丁系列（v12，共25个补丁）解决 Intel 应用能耗遥测（AET）必须将 INTEL_PMT_TELEMETRY 编译进内核（=y）的问题。原方案虽能枚举 AET 事件，但导致配置复杂、内核内存占用增加，且无法通过卸载并加载新版模块来修复问题，用户难以接受。补丁在 AET 代码中新增注册函数，供 INTEL_PMT_TELEMETRY 提供枚举功能，使该模块可独立于 resctrl 文件系统的挂载/卸载而加载或卸载：每次挂载时执行枚举，每次卸载时进行清理。系列基于 v7.3-rc3。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### x86/mm: Allow preemption while waiting for kernel TLB flushes
- https://lore.kernel.org/all/20260921095359.3784458-1-zhouchuyi@bytedance.com/
- 本补丁系列（共5个）延续 IPI 完成等待可抢占的工作，处理此前被推迟的 flush_tlb_kernel_range()。内核范围 TLB 刷新需向所有在线 CPU 发送请求并同步等待，最慢 CPU 会拖累整体，而全程禁用抢占会阻塞发起 CPU 上的高优先级任务。由于内核刷新并不使用 initiating_cpu 等 mm 相关字段，系列将其数据与 flush_tlb_info 解耦：全刷新无需描述符，范围刷新只需 start/end，从而去掉多余初始化及其抢占限制。五个补丁依次完成：统计内核刷新请求、复用 kernel_tlb_flush_all()、抽取阈值判断、解耦描述符、移除外层抢占保护（INVLPGB/TLBSYNC 仍受保护）。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Allow preemption during IPI completion waiting to improve real-time performance
- https://lore.kernel.org/all/20260318045638.1572777-1-zhouchuyi@bytedance.com/
- 本补丁系列（v3，共12个补丁）旨在让 IPI 完成等待过程可被抢占，以改善实时性。现有 smp_call_function*() 全程禁用抢占，x86-64 上 TLB 刷新依赖 IPI，进程退出或页回收时需等待大量 IPI，导致当前 CPU 抢占延迟激增，生产环境中 16 核机器上观测到高达 16ms。补丁通过 RCU 等机制保护 per-CPU 数据并与 CPU 下线同步，使 csd_lock_wait() 可抢占，缩短禁抢占临界区。效果显著：TLB 刷新路径不再出现超过 1ms 的禁抢占，最大禁抢占 P99 从约 16.7ms 降至约 1.5ms，降幅约 90.7%，剩余延迟主要源于锁竞争。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: make the vmlinux BTF an on-demand loadable module (CONFIG_DEBUG_INFO_BTF=m) to save ~5.4 MB memory
- https://lore.kernel.org/all/20260923053948.30617-1-wanjay@amazon.com/
- 本补丁系列（bpf-next，共6个补丁）将 CONFIG_DEBUG_INFO_BTF 改为三态，支持 =m：vmlinux BTF 不再编入内核镜像，而由 btf_vmlinux.ko 承载，首次需要时按需自动加载，未使用 BTF 的系统可省约 5.4MB 内存，使用后行为与 =y 一致。实现上：验证器仅在程序引入内核类型时才取 BTF；kfunc、dtor kfunc、struct_ops 注册延迟排队后重放；先于 vmlinux BTF 加载的模块 BTF 暂存并在其到达后解析注册；通过内置的大小与 SHA-256 校验防止镜像不匹配；.BTF 保留为不可加载 ELF 段以兼容 pahole/bpftool。=m 下禁用 BPF_PRELOAD。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add dmabuf read/write via io_uring
- https://lore.kernel.org/all/cover.1789997898.git.asml.silence@gmail.com/
- 本补丁系列（v6，共13个补丁）为 io_uring 增加对 dmabuf 的直接读写支持：可针对指定文件将 dmabuf 注册到 io_uring 实例，之后像普通“注册缓冲区”一样配合 IORING_OP_READ/WRITE_FIXED 使用。该基础设施不局限于 io_uring，未来可有更多使用者。文件需实现新的 file operation 才能启用，本系列仅支持 NVMe 块设备；映射经新的迭代器类型在 I/O 栈中传递，并配套请求计数、生命周期管理与失效处理。补丁分为通用 API、块层、NVMe 及 io_uring/UAPI 四部分，基于 Jens 的 for-next，已在多种设备上测试，udmabuf IOMMU 优化下性能提升显著（STRICT 模式由 570 KIOPS 增至 5.01 MIOPS）。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### PCI: Add support for ACS Enhanced Capability
- https://lore.kernel.org/all/SI2PR01MB43935D2C01946E6D8FD9EFAADC832@SI2PR01MB4393.apcprd01.prod.exchangelabs.com/
- 本补丁系列（v10，共6个补丁）改进内核 ACS 实现并新增对 PCIe Gen5 引入的 ACS 增强能力（ACS Enhanced Capability）的支持。改进包括：按设备实际能力而非通用内核掩码校验 ACS 使能标志，仅启用受支持特性；将分隔符解析统一到 pci_dev_str_match()；拆分 disable_acs_redir 与 config_acs 参数逻辑为独立函数以提升可维护性与解析健壮性；完善 config_acs 文档（多设备配置示例及引号用法）。增强 ACS 提供更强的设备隔离，对虚拟机直通场景的安全至关重要，在支持 PCI_ACS_ECAP 的硬件上默认启用，可通过 config_acs= 配置；pci_acs_enabled() 增加对根端口和下行端口的相应检查，并对不支持的旧设备跳过检查以保持兼容。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### iommufd: Infrastructure for vIOMMU creation for confidential guests and guest TSM requests
- https://lore.kernel.org/all/20260917140159.1163281-1-aneesh.kumar@kernel.org/
- 本补丁系列（RFC v6，共11个补丁）为设备直通提供 IOMMUFD 与 PCI/TSM 基础设施，面向机密虚拟机场景。它引入由 IOMMUFD 管理的 vIOMMU 提供者注册机制和 IOMMU_VDEVICE_TSM_REQ ioctl，使物理 IOMMU 驱动之外的子系统也能实现某种 vIOMMU 类型：将 vIOMMU 操作与其模块属主、私有数据绑定，并在分配 vIOMMU 时可被发现。外部提供者按 vIOMMU 类型精确匹配，无匹配时回退到物理 IOMMU 驱动；一旦匹配则以其结果为准，失败不再回退。来自客户机的 TSM 请求经 vdevice 分发，PCI/TSM 采用引用计数上下文保留所需资源，无需新增单独的 TSM bind/unbind ioctl。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### blk-iocost: BPF struct_ops cost model
- https://lore.kernel.org/all/20260918031751.1255420-1-cui.tao@linux.dev
- 本补丁系列（RFC v5，共5个补丁）为 blk-iocost 引入可插拔的 BPF struct_ops 成本模型，兑现 iocost 当年“用 BPF 实现成本模型”的承诺，沿用 TCP 拥塞控制的注册模式：内置线性模型仍为默认，新算法可用 BPF 原型验证。内置模型依赖单游标顺序/随机判定与 16MB 阈值，存在启发式僵化（同 cgroup 多顺序流被误判，实测 89 倍超额计费）、设备非线性、flush/zone append 未计费等定价错误，进而扭曲整个控制环。新接口提供 calc_cost() 及 blkcg 上下文与在线/离线回调，通过 io.cost.model 的 model=<name> 绑定，model=linear 恢复内置。附带 2 倍示例模型、多流检测模型、tracepoint 与文档，未挂载时无可测开销。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### blk-iocost: charge flushes and zone appends
- https://lore.kernel.org/all/20260922043856.2020116-1-cui.tao@linux.dev/
- 本补丁系列（v4，共4个补丁）修复 blk-iocost 对 flush 与 zone append 不计费的问题。测试发现权重仅 1% 的 cgroup 可无限制发起 flush，12 秒内产生约 51 万次而 cost.usage 始终为零，设备被独占却无任何记账；zone append 同样因内置线性模型只定义读写系数而被计为零成本并排除在延迟统计外。补丁为 io.cost.model 新增 flushiops 系数（VTIME_PER_SEC/flushiops），对 REQ_PREFLUSH 额外计一次 flush，对无原生 FUA 设备的 REQ_FUA 再计一次；将 zone append 按写操作定价并纳入延迟窗口统计；另修正过时注释。flushiops 默认为零，不影响现有配置。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: madvise: drop MADV_PAGEOUT folios at swap writeback completion
- https://lore.kernel.org/all/20260921152449.629486-1-alex@ghiti.fr/
- 本补丁优化 madvise 的 MADV_PAGEOUT：在异步交换设备上，原先只把 folio 标记 PG_reclaim 并在回写完成后移到非活跃链表尾部，内存要等后续回收扫描才真正释放。补丁改为在隔离时将这些 folio 标记为 dropbehind，由 folio_end_writeback() 在每次写入完成时直接将其从交换缓存中丢弃。由于 dropbehind folio 由完成回写者释放，提交者必须在提交写请求前释放引用，并像回收路径释放 folio 前那样先刷新待处理的 TLB 批次。注意此后 dropbehind folio 的 nr_reclaimed 在写提交时即计入，而非实际释放时，因为回收者不会再见到该 folio。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: make userland page table freeing RCU-safe
- https://lore.kernel.org/all/20260922-rcu-pagetable-freeing-v4-0-fe1ad1f1e303@kernel.org/
- 本补丁系列（v4，共12个补丁）将内核中剩余架构全部转为在 RCU 宽限期后才释放用户态页表，并彻底移除 CONFIG_MMU_GATHER_RCU_TABLE_FREE 及相关代码。这使得仅凭 RCU 即可安全地无锁遍历页表，降低锁竞争、避免锁序问题，并删除大量架构特定代码。改动大多是机械性的配置切换，但 sh-X2、m68k-motorola 和 sparc32 需特殊处理：利用页表对齐的低位编码页表层级以定制释放逻辑；因 call_rcu() 可能在软中断上下文释放，m68k-motorola 与 sparc32 需改用 IRQ 安全的自旋锁。全部改动经构建测试，三个重点架构还通过启动与大量页表释放压力测试验证。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: distinguish HW PTE pointers from SW PTE value pointers
- https://lore.kernel.org/all/20260922-pte0-v3-0-5670b8cb9059@arm.com
- 本补丁系列（v3，共9个补丁）在 PTE 层面区分硬件页表槽位与软件 PTE 值。当前 pte_t 兼表两者，pte_t * 既可指向栈上的软件 PTE 值，也可指向页表槽，编译器无法区分，易导致误用或绕过架构访问器直接解引用。系列引入 hw_pte_t 作为 PTE 表存储的元素类型，并将通用 MM 转为使用 hw_pte_t *，软件值仍用 pte_t，返回值型参数统一命名为 ptentp。未选择 ARCH_HAS_HW_PTE_T 时 hw_pte_t 即 pte_t，本系列无架构启用，行为完全不变；PMD 及以上层级暂不涉及。已在 x86_64 与 arm64 上测试，无回归。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Orphaned Virtual Machines
- https://lore.kernel.org/all/20260920193650.3373435-1-pasha.tatashin@soleen.com/
- 本 RFC 系列（共46个补丁）是为 LPC'26 KVM Microconf 准备的概念验证，展示“孤儿虚拟机”（OrphanVM）在宿主内核热更新（kexec）期间于保留的物理 CPU 上不中断运行。架构分四层：KHO/LUO 负责跨 kexec 保留 guest_memfd、二级 MMU 页表与 vCPU 状态；cpu_preserve 将选定物理 CPU 下线进入专用 park 循环并切换到仅映射保留代码/数据的隔离地址空间，由 modpost 与 objtool 做编译期段隔离检查；oncore 在保留核上提供运行队列与时间片调度；KVM Caretaker 直接进入客户机执行，支持 Intel VMX、AMD SVM 与 ARM64 VHE，新内核启动后回收 CPU 并恢复执行。系列按八个工作流分拆，不打算整体合入，仍处早期阶段。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kallsyms: Accelerate symbol name lookups by ~19x
- https://lore.kernel.org/all/20260919-ksyms-tune-v1-0-d85c97da1a32@gmail.com/
- 本补丁系列（共3个补丁）将 kallsyms 符号名查找加速约 19 倍。原实现的二分查找存在两大瓶颈：get_symbol_offset() 需从最近的 256 符号标记顺序扫描，平均每次探测解码约 128 个 ULEB128 头部；kallsyms_expand_symbol() 在 strcmp 前把整个候选符号解压到 512 字节栈缓冲区，而约 94% 的探测在头一两个字符即不匹配。补丁1 新增微基准测试模块；补丁2 引入构建期生成的 3 字节直接索引 kallsyms_names_offsets，使偏移查找变为 O(1) 并移除 kallsyms_markers[]；补丁3 新增 kallsyms_strcmp_symbol() 边解压边比较、首字符不匹配即退出。实测命中 4370ns 降至 247ns，指令数减半，缓存未命中降 99%，代价为 .rodata 增加约 573 KiB；地址转名与顺序遍历性能不变。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### perf: Add support for memory region/range reporting
- https://lore.kernel.org/all/20260909160218.174928-1-thomas.falcon@intel.com
- 该 v7 系列为 perf 工具新增两项内存相关报告功能：1）在 perf-c2c 和 perf-script 中报告内存区域（region），源自 Off-module Response（OMR）机制，支持除缓存区域外最多 8 个细粒度内存区域；2）在 perf.data 文件头和 perf-c2c 中加入内存范围（range）数据，源自 ACPI MRRM 表，提供每个内存范围的基址、长度、NUMA 节点及本地/远程区域 ID。此外允许 perf-mem 输出中打印 PERF_MEM_LVLNUM_L0。v7 修复了 perf-c2c 中 output_str 分配错误处理导致的内存泄漏。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: BPF-driven proactive memcg reclaim
- https://lore.kernel.org/all/cover.1789091855.git.zhuhui@kylinos.cn
- 该 bpf-next v10 系列新增 `bpf_proactive_reclaim()`——一个可睡眠 kfunc，让 BPF 程序能对指定 memcg 主动执行一次回收。此前 BPF 可观测 cgroup 内存压力，却无法触发回收（需写 memory.reclaim）。该 kfunc 限定为 BPF_PROG_TYPE_SYSCALL，确保在干净进程上下文运行，避免文件系统锁或 NOFS/NOIO 下死锁；可通过 bpf_wq/task_work 异步排队。典型用例：监控高优先级 cgroup，压力上升时异步从低优先级 cgroup 回收内存。基准测试显示受压负载完成时间中位数从 12.0s 降至 2.1s，提速 51%–90%。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/damon: hardware-sampled access reports
- https://lore.kernel.org/all/20260910171623.6638-1-ravis.opensrc@gmail.com
- 该 RFC v2 系列让 DAMON 从硬件采样器（而非页表扫描）获取访问信息，并以采样结果加权方案评分。它基于 mm-new 的数据属性探针框架，将 PMU 表达为上下文的一个探针。核心是新增统一的上报机制：NMI 上下文源通过每 CPU 无锁环上报访问地址，按探针类别分区（全局缺页环与每上下文 perf 环），由 kdamond 在聚合边界排空并映射到区域探针命中数。已在 Intel PEBS、AMD IBS 上测试，并支持 ARM SPE。借此可在同一上下文中，用带宽测量（resctrl MBM）驱动热页分布、按区域年龄降级冷页，实现无需目标比例的自动内存分层，且带宽非瓶颈时自动回退为延迟优先分层。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: Introduce section-based vmemmap optimization for HugeTLB
- https://lore.kernel.org/all/20260910063256.64386-1-songmuchun@bytedance.com/
- 该 v6 系列从更大的"泛化 HugeTLB 与 device DAX 的 HVO"系列中拆出，聚焦一个自包含步骤：让通用稀疏 vmemmap 代码支持基于内存段（section）的优化，并将 HugeTLB bootmem 页面切换到该路径。当前 HugeTLB vmemmap 优化有独立的早期启动路径，在通用 sparse-vmemmap 代码前预填充优化映射，难以与其他用户共享，并在通用初始化流程中遗留大量 HugeTLB 专属启动状态。新方案改由 HugeTLB 在对应内存段中记录复合页 order，通用填充路径据此分配或复用共享尾部 vmemmap 页。17 个补丁依次准备元数据、改造通用路径、切换 HugeTLB，并清理冗余代码。device DAX 转换与更广泛的 HVO 整合留待后续。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### io_uring/nvme: support fixed buffer for metadata
- https://lore.kernel.org/all/20260909222836.2475352-1-csander@purestorage.com
- 该系列为 io_uring NVMe passthrough 增加对元数据使用"固定"（已注册）缓冲区的支持。此前仅数据支持固定缓冲区，而在高 IOPS 负载下，元数据页的 pin/unpin 开销显著，可通过固定元数据缓冲区避免。元数据与数据的固定缓冲区索引可独立指定或省略——这很重要，因为元数据缓冲区常存于不同内存（如 ublk 零拷贝下数据是内核注册缓冲区、元数据是用户态注册缓冲区，无法共享索引）。当前实现中，io_uring_cmd 层存储元数据缓冲区节点，NVMe passthrough 层定义 UAPI。作者主要疑问是该功能应归属哪一层：核心 io_uring、io_uring_cmd 还是 NVMe passthrough，并权衡了通用复用与有限的 sqe/io_kiocb 空间。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kernfs, driver core: Cut per-node lock traffic in bulk registration
- https://lore.kernel.org/all/20260911-vfopt-s3-v1-0-66e3602f76f7@amazon.de/
- 该系列针对并行注册 VF 时在 kernfs 与驱动核心中遇到的三处锁开销进行优化。两处随 sysfs 节点数增长：kernfs root rwsem 每节点写锁两次、每个 inode ID 在 kernfs_idr_lock 下分配；第三处随设备数增长：get_device_parent() 的 glue 目录查找在全局 gdp_mutex 下线性遍历，导致二次复杂度。补丁1让节点在同一次 kernfs_rwsem 写持有中激活并链接，每节点仅一次写锁；补丁2用按父 kobject 索引的红黑树替代线性遍历；补丁3以每 CPU 批量（16 个）预分配 inode ID 并经 idr_replace RCU 存储，将 idr_lock 获取减少 16 倍。锁统计显示各项获取次数与持有时间明显下降，但残留的 iommu_probe_device_lock 主导了测试窗口，掩盖了本系列的实际墙钟收益。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### iommu/vt-d: Introduce trusted DMA initialization support
- https://lore.kernel.org/all/20260915074235.1219183-1-baolu.lu@linux.intel.com/
- 该系列为主机 Intel IOMMU 驱动添加 VT-d 可信扩展支持，作为 TEE I/O 可信 DMA（如 TDX Connect）的基础。该扩展为机密设备分配引入平行的专用可信 DMA 路径，常规主机 DMA 行为保持不变。VT-d 增强包括：1）受 SEAM SAI 限制的可信 DMA 翻译根表；2）可信失效队列；3）启用 TDX Connect 时限制 VMM 的 DID 并保留 DID 最高位供 TDX 模块使用。主机为 TDX 模块的可信 DMA 数据结构分配内存，并经 SEAMCALL 请求在各 IOMMU 中启用扩展；非 TEE-I/O 请求不受影响。本次仅聚焦 VT-d 侧启用，上层 TDX 客户机/设备流程另行提交。五个补丁分别实现 SEAMCALL 封装、元数据页需求解析、核心入口、元数据分配与配置、DID 空间限制。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### arm-mpam: Add basic device tree support for resctrl
- https://lore.kernel.org/all/20260914-mpam-resctrl-dt-knp-support-v2-0-bf6645bb2f65@oss.qualcomm.com/
- 该 RFC v2 系列为基于设备树（DT）的平台添加 Arm MPAM（内存系统资源分区与监控）配合 resctrl 的基础设备树支持。MPAM 在 DT 平台上启用前需要 DT 绑定与解析支持。该系列建立在 James Morse、Shanker Donthineni 和 Rob Herring 尚未上游的 MPAM 快照补丁之上，保留原作者署名并标注改动。内容包括：对现有主线代码的独立修复（RIS 索引范围检查、MSC MMIO 窗口大小 off-by-one）；继承的 MSC 绑定、cacheinfo 缓存 ID 生成、MSC 探测与内存控制器 DT 支持；以及新增的 schema 修复、foundling MSC 创建修复和基于 per-RIS 节点派生 MSC 可访问性的回退机制。MSC 的 CPU 亲和性由父设备派生，父节点为通用容器时经 per-RIS 回退解析。作者征询原作者是否同意接手扩展以避免重复工作。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### PCI/IOV: Initialize virtual functions in parallel
- https://lore.kernel.org/all/20260911-vfopt-s1-v1-0-693271dc0226@amazon.de/
- 该 RFC 系列（S1）为 SR-IOV 引入 VF 并行初始化。在基于 kexec 的实时更新（LUO）场景中，现代硬件每 PF 有数百至数千个 VF，SR-IOV 使能成为停机时间瓶颈。本系列通过并行初始化对各子系统施压，后续四个系列（S2-S5）再逐一攻克序列化瓶颈。在配备数千 VF 的双路 arm64 Neoverse V2 服务器上，五个系列合计将 SR-IOV 初始化时间缩短 65%；本系列单独贡献不足 5%，主要收益来自后续系列消除阻碍并行发挥效果的序列化。作者主要依赖 lock_stat 数据佐证改进，但残留的 iommu_probe_device_lock 主导测试窗口，掩盖了后续系列的墙钟收益。附带可复现的 QEMU/KVM 测试镜像，征询整体优化设计反馈。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### arm_mpam: Add MPAM-Fb firmware support
- https://lore.kernel.org/all/20260911112835.714162-1-andre.przywara@arm.com/
- 该 v10 系列为 arm_mpam 添加 MPAM-Fb 固件支持，实现基于固件的 MSC 访问。Arm MPAM 规范中的内存系统组件（MSC）通常经 MMIO 寄存器访问，但某些场景（位于独立总线、仅安全映射、跨插槽无直接 MMIO、访问过慢或需过滤、集成有缺陷）下过于受限。MPAM-Fb 规范提供替代访问方式：将 MSC 访问封装为消息，经共享内存/邮箱系统（类似 SCMI）通信，ACPI 系统通过 PCC 通道抽象。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched/numa: stop VMA scan filters from gating promotion
- https://lore.kernel.org/all/20260911001826.2109390-1-gourry@gourry.net/
- 该 v2 系列针对 NUMA balancing 中的问题：其提示缺页同时用于任务放置和内存分层提升，但为避免无效插槽放置而设计的过滤器也会阻碍提升。只读文件映射、无近期 PID 活动的 VMA 可能永不被扫描，共享 folio 也被下层拒绝，导致这些映射中的热内存永久滞留在慢速层。方案是将"仅提升"扫描与"插槽放置"扫描分离：通过 MM_CP_PROT_NUMA_PROMO_ONLY 标志在单次保护遍历中携带该选择，使 PTE/PMD 路径可将提示缺页限制为提升候选，避免 per-mm 状态。改动允许合格共享 folio 提升、扫描只读文件映射与 PID 非活动 VMA 进行提升、并单独追踪放置扫描以防提升扫描推迟放置饥饿回退。在 768GB/256GB DRAM/CXL 主机测试，DRAM 带宽提升、CXL 降载、请求延迟显著下降。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kbuild: significantly speed up kernel builds
- https://lore.kernel.org/all/20260914-build-speedup-v2-0-39817ec5db23@kernel.org/
- 该 v2 系列大幅优化内核编译速度：allmodconfig 完整构建最多快 36%、增量构建最多快约 70%、空操作构建最多快约 90%，在所有测试设备（Threadripper、EPYC、M2）上均有提升。核心方法是尽可能并行化单线程任务并提高构建流程代码效率，涉及 kbuild、kallsyms、modpost、objtool、mksysmap 和 Rust 构建系统。主要改动包括：kallsyms 引入缓存并直接读取 ELF 符号表而非用 nm；避免不必要排序；实现对象追踪缓存与更高效的依赖时间戳检查；模块描述符改用汇编（*.mod.S）而非 C，速度提升 10 倍；objtool 多线程解码大对象；Rust 前端可多线程运行并与 C 并行构建；默认使用并行 gzip（pigz）。在多架构上通过 System.map 一致性、启动、模块加载与 kallsyms 自测验证。开发中广泛使用 LLM 定位瓶颈并生成代码，作者人工审计、重写并验证正确性，每个提交带 Assisted-by 标签。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Huge mapping support for protected VMs
- https://lore.kernel.org/all/20260911135053.146435-1-vdonnefort@google.com
- 该 v2 系列为 pKVM 保护型虚拟机添加大页映射支持。目前 pKVM 严格以 PAGE_SIZE 粒度处理 stage-2 映射与所有权跟踪；本系列将其扩展至支持 PMD_SIZE 块映射，从而为受保护客户机启用透明大页（THP）。hugetlbfs 因非 swapbacked 暂不支持。主要改动包括：1）在 host stage-2 上启用块级注解，使 host->guest 捐赠转换时的 GFN 注解匹配客户机 stage-2 映射大小；2）扩展所有权转换 HVC 以支持 PMD_SIZE；3）实现 PKVM_HYP_REQ_SPLIT 管理程序请求，允许 hypervisor 要求主机拆分映射，确保客户机 stage-2、pkvm_mapping 树与 host stage-2 映射大小一致；4）当 transparent_hugepage_adjust() 确认 VMM stage-1 存在大页映射时，为保护型 VM 使用 PMD_SIZE 映射。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: arm64: Add Statistical Profiling Extension (SPE) support
- https://lore.kernel.org/all/20260903160623.315525-1-alexandru.elisei@arm.com/
- 该 RFC v7 系列为 KVM/arm64 添加统计性能扩展（SPE）支持。相比 v6 完全改变思路：用 guest_memfd 支撑 VM 内存并通过 KVM_PRE_FAULT_MEMORY 在运行首个 VCPU 前将整个内存钉在 stage 2，大幅简化代码。由于内存全钉住，无需虚拟化最大缓冲区大小，PMBIDR_EL1/PMSIDR_EL1 无需陷入，去除对 FEAT_FGT 的依赖；支持 SPE 主机驱动作为模块加载。KVM 支持基本简化为配置该特性的用户态 ABI 及 SPE 状态上下文切换。用户态通过 KVM_SET_DEVICE_ATTR 设置 SPE 特性、中断号、PMU 实例并调用 KVM_ARM_VCPU_SPE_INIT。系列依赖 arm64 的 KVM_PRE_FAULT_MEMORY 实现、忽略 guest_memfd MMU 通知、脏页日志支持等前置补丁。迁移处理较 hacky：引入新硬件退出原因，启用脏页日志时让启用缓冲区的 VCPU 退出到用户态。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: Reduce struct page overhead for FS-DAX pmem
- https://lore.kernel.org/all/20260903122128.12264-1-songmuchun@bytedance.com
- 该系列旨在减少 FS-DAX pmem 的 struct page 开销。AI/代码执行服务常用短生命周期沙箱 VM，用 virtio-pmem 配 FS-DAX 可降低内存占用，但 guest 需为整个 pmem 区间预先分配并初始化 ZONE_DEVICE 元数据（约占设备 1.56%），拖慢启动。系列观察到：稀疏镜像的空洞及仅通过 read/write 访问的块无需私有 per-PFN struct page。方案将 vmemmap 填充与私有元数据分配分离——注册时所有 PFN 的 vmemmap 先指向共享只读页（含通用 ZONE_DEVICE 状态），仅在 DAX 缺页将 PFN 插入用户映射前才按需实体化私有可写元数据（PTE 缺页materialize单页，PMD 缺页materialize整个 PMD 范围）。未缺页的 PFN 持续用共享页，省内存和初始化开销。后续可反向恢复。四个补丁分别重命名架构开关、避免触碰干净页 PG_hwpoison、添加共享只读基础设施、令 pmem FS-DAX 启用新模式。数据路径语义不变。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Introduce NVIDIA vGPU manager and VFIO variant driver
- https://lore.kernel.org/all/20260905081116.106613-1-zhiw@nvidia.com/
- 该系列引入 NVIDIA vGPU 管理器（集成于 nova-core）及消费其生命周期接口的 VFIO 变体驱动。控制路径为：guest 驱动→QEMU→VFIO core→vGPU VFIO 变体驱动，变体驱动绑定 PCI VF 并通过 PF 生命周期 API 与 nova-core（PF 驱动/vGPU 管理器）交互。nova-core 侧负责面向 GPU 固件（GSP-RM）的 vGPU 管理，扩展了 VMMU/FIFO 信息保留、VRAM/BAR1 管理、GMC 事务、插件启动/关闭、帧缓冲擦除、debugfs 日志、48-VM WPR2 堆选择等。VFIO 侧仅绑定通过 driver_override 指定的 VF，派生 GFID，其余委托 vfio-pci-core。跨模块接口仅 open/close/reset 三个 GPL 符号，生命周期在 open/reset/close 三点划分所有权。这是此前 RFC 的重构，将 vGPU 管理器从 VFIO 移入 nova-core。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### coredump, files: exit files on request
- https://lore.kernel.org/all/20260902-work-coredump-unlock-self-v2-0-1bece368cbb1@kernel.org/
- 该 RFC 系列让 coredump socket 可请求线程组在生成核心转储前同步关闭各 fdtable。核心是新增同步关闭 fdtable 的原语，性能提升可观：对拥有大量文件描述符的进程，可省去大量 cmpxchg 和 task_work 操作。基准测试（64 vCPU）显示退出、execve、close_range 场景约 7-11% 提升，即每关闭一个文件恒定省 15-25ns，多进程竞争时优势增至 13-15%。作者细致分析了内核线程、io_uring/vhost worker 等特殊情况，确认所改路径不被 kthread 采用。close(2) 不受影响。启用 COREDUMP_CLOSE_FILES 后，转储线程分配空 fdtable，唤醒组内各线程切换并释放旧表，解决长时间持锁问题，但因文件可跨进程共享无法完全保证。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### arm64/mm: Enable 128 bit page table entries
- https://lore.kernel.org/all/20260907035030.2839978-1-anshuman.khandual@arm.com
- 该补丁系列为 arm64 启用 128 位页表项，支持 ARMv9.3 起可选的 FEAT_D128 特性（VMSAv9-128 翻译系统）。128 位页表项提供更大的物理/虚拟地址范围及更多 MMU 特性位。新增 ARM64_D128 配置项，让用户在构建时选择 VMSAv8-64（D64）或 VMSAv9-128（D128）；D128 内核若在硬件上未检测到 FEAT_D128 则会卡住（新增 CPU_STUCK_REASON_NO_D128），无法回退到 D64，且仅在 CONFIG_EXPERT 下可用。D128 每级条目更少，页表几何结构随之改变。目前尚不支持 52 位 VA/PA、KVM 和 UNMAP_KERNEL_AT_EL0。MM 自测无明显问题。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Reclaimable kernel stacks
- https://lore.kernel.org/all/20260827232948.2520558-1-stevensd@google.com
- 该 RFC 提出可回收内核栈方案：在任务阻塞且安全时部分回收其栈内存。Android 系统常有数千线程，多数长期阻塞，内核栈占用 1-2% 系统内存，回收可降低约 50%。方案通过调度器钩子跟踪阻塞状态，用 shrinker 异步回收栈顶以外的页，任务被回收后需重新填充栈才能重调度（含快速路径和 workqueue 慢路径）。为避免回收死锁，仅对不持有回收依赖锁的任务回收，用新的 PF_RECLAIMABLE_STACK 标志标注安全阻塞点（10 个标注覆盖 Android 95% 线程）。副作用是可能增加 OOM 击杀。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### iommu/arm-smmu-v3: Adopt the crashed kernel's stream table for kdump
- https://lore.kernel.org/all/cover.1788130528.git.nicolinc@nvidia.com/
- 该补丁系列让 ARM SMMUv3 在 kdump 时沿用崩溃内核的流表。当前 SMMU 驱动探测时会激进复位硬件（清 SMMUEN、设 GBPA 为 ABORT），在 kdump 场景下会中止在途 DMA 引发 AER/SError 甚至 panic，或旁路 SMMU 破坏内存。因架构规定 SMMUEN=1 时改 STRTAB_BASE 不可预测，kdump 内核只能沿用崩溃内核的流表。系列新增 ARM_SMMU_OPT_KDUMP_ADOPT，跳过 SMMUEN/STRTAB_BASE 复位及队列设置，映射旧流表、保留在用 ASID/VMID 防 TLB 混叠、延迟默认域附加。代码集中于两个新文件，本次仅修复一致性 SMMU。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### vfio/pci: Handle PCI error recovery and report state to userspace
- https://lore.kernel.org/all/20260901093217.8539-1-skolothumtho@nvidia.com/
- 该 RFC 让 vfio-pci 参与 PCI 错误恢复并向用户态报告状态。当前 vfio-pci 仅实现 error_detected()，忽略通道状态、对所有错误都返回 CAN_RECOVER，且无 slot_reset/resume，用户态只收到一个空 eventfd，无法区分可恢复错误与永久故障，导致 QEMU 直接终止 VM。系列扩展 error_detected() 并新增 slot_reset()、resume()，恢复期间阻断设备访问、撤销 BAR 映射与 DMA-BUF、按严重程度投票；新增 VFIO_DEVICE_FEATURE_PCI_ERROR_RECOVERY uAPI，通过 eventfd 及状态字加序列号报告恢复进度。该功能为可选启用，并需处理 recovery_lock 与 pci_bus_sem 的锁序问题。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### FBE virtualization: inline encryption for virtio-blk guests
- https://lore.kernel.org/all/20260827160806.1295313-1-linlin.zhang@oss.qualcomm.com/
- 该补丁系列为 virtio-blk guest 实现基于内联加密的文件加密（FBE）。当前 virtio-blk 在提交 bio 时丢弃 crypto 上下文，无法支持内联加密。在高通 GVM 平台上，ICE 硬件由 host 与 guest 共享，guest 无法直接访问，只能通过 VIRTIO_BLK_F_INLINE_ENCRYPTION 随每个 I/O 提交虚拟 keyslot 索引和 DUN，由 host 将虚拟槽转换为物理 ICE 槽并提交 bio，不跨 VM 边界传输原始密钥。补丁1-4 为 guest 侧（含 dt-binding），补丁5-8 为 host 侧核心设施（含 /dev/blk-crypto-proxy），补丁9-11 为高通平台实现。仅测试了 AES-256-XTS。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: arm64: Add kernel replication feature
- https://lore.kernel.org/all/20260827161158.3618409-1-panov.nikita@huawei.com/
- 该 RFC 为 arm64 平台实现内核文本与只读数据的 NUMA 复制，处于早期 PoC 阶段。功能包括：按 NUMA 节点复制内核 text/rodata、vmalloc 支持复制（模块 text/rodata 也复制）、兼容 KPROBES/KGDB/KPTI/KASLR/KASAN，仅复制相关的部分翻译表，支持 4K/64K 页并提供 kernel_replication 命令行开关。开销约每节点 30MB 内存，CPU 开销主要在启动阶段。微基准显示远端节点执行时间最多降低 70%，客户实测 CEPH、StarRocksDB 提升约 5%。已知问题包括其他页大小组合、vmalloc 表非本地、PGD 级修改（如内存热插拔）同步缺失。作者希望讨论该特性是否应合入主线。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: Switch device DAX to section-based vmemmap optimization
- https://lore.kernel.org/all/20260831075342.57563-1-songmuchun@bytedance.com/
- 该补丁系列将 device DAX 切换到为 HugeTLB 引入的基于 section 的稀疏 vmemmap 优化基础设施，是从更大的"通用化 HVO"系列拆分出的自包含步骤。此前 device DAX 使用旧的 DAX 专用填充模型，含单独的尾部 vmemmap 页预留和架构特定逻辑。本系列让 device DAX 从 pgmap->vmemmap_shift 设置 section order，使用通用的每-zone 共享尾页，去除额外预留页；powerpc radix 路径也改用相同的共享尾页 helper。前几个补丁引入通用 CONFIG_SPARSEMEM_VMEMMAP_OPTIMIZATION 符号并抽出共享尾页分配，中间补丁完成迁移，最后更新文档。更广泛的 HVO 整合留待后续。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/damon: introduce data access-as-a-data attribute
- https://lore.kernel.org/all/20260901043417.2165-1-sj@kernel.org/
- 该补丁系列扩展 DAMON 的数据属性监控系统，支持基于页表 accessed 位和 PG_idle 的访问监控，将"数据访问"本身作为一种数据属性。以往使用 probe weights 时 DAMON 会停止访问监控，无法同时兼顾数据属性与访问模式。系列新增 pgidle_unset probe 过滤类型（判断页是否被访问过），并引入 prep actions 功能及 set_pgidle 准备动作（清除 accessed 位、设置 PG_idle），使 probe 模式能像经典模式一样监控访问。测试表明 probe 方式结果与经典方式相似。前4个补丁引入新过滤类型，后13个引入准备动作功能，含 sysfs 接口、selftest 和文档更新。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: arm64: New PTE dirty-page encoding, HAFDBS new usage
- https://lore.kernel.org/all/20260901171558.2674031-1-leo.bras@arm.com/
- 该 RFC 系列有两个主要目标：一是补丁 #1-#3 修改 PTE 描述符，利用 DBM 位采用 WD/WC/RO 编码并适配所有用法，同时引入新的 walker 用于清理脏位——若为块映射（大页）则清除 DBM 位，以便懒分裂时能触发写错误，这对后续补丁及 HDBSS/HACDBS 启用都必要。二是补丁 #4-#5 探索在 guest 上使用 HAFDBS，避免脏日志开启时把所有 PTE 重置为 WC，从而加速启动。作者希望在脏日志之外用 HAFDBS 仅标记真正被写入的页，减少遍历页表时的原子写，代价是清理前需通过新的 vcpu 请求在每个 vcpu 上禁用 HAFDBS。作者征求该方向是否值得推进的反馈。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2026年 第08期 (Start From 2026/08/01)

#### KVM: arm64: Add KVM_PRE_FAULT_MEMORY support
- https://lore.kernel.org/all/20260825-kvm-arm-prefault-v1-0-befe8947702e@kernel.org/
- 该补丁系列为 arm64 实现 KVM 阶段2页表预错误（KVM_PRE_FAULT_MEMORY）功能。基础部分改造 kvm_s2_fault_desc，使其独立存储 ESR 和 kvm_s2_mmu，并让中止路径返回 granule 大小，同时支持在 MMU 读锁下遍历页表以实现并行。实现部分在 kvm_arch_vcpu_pre_fault_memory() 中，通过遍历页表、对未映射页发起合成缺页来预映射指定 GPA。不支持 pKVM。该系列基于 Jack Thomson 的工作并包含其测试用例。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### fuse: zero the partial EOF page when extending a file
- https://lore.kernel.org/all/20260824143052.1546163-1-jamz@amazon.com
- 该补丁系列修复 fuse 文件系统扩展文件时的缺陷：当越过非页对齐的 EOF 扩展文件时，旧末页尾部未被清零，若该页已被 mmap 弄脏，则新进入范围的尾部会向后续读返回陈旧数据，违反 POSIX 文件扩展语义。补丁1在缓冲写、setattr、fallocate 三条扩展路径上预先调用 truncate_pagecache_range() 清理新暴露范围；补丁2新增基于 /dev/fuse 的自测覆盖各路径。已在 UML 下启动测试并用 libfuse 的 passthrough_ll 复现验证。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「fuse: zero the partial EOF page when extending a file」）

#### fuse: allow FUSE_SYNCFS for privileged userspace servers
- https://lore.kernel.org/all/20260820130158.254808-1-jamz@amazon.com/
- 该补丁系列让普通 /dev/fuse 服务器也能启用 FUSE_SYNCFS（将 syncfs()/sync() 传播到服务端）。此前仅 virtiofs 和 fuseblk 支持，因不可信服务器会阻塞 sync。系列新增 FUSE_HAS_SYNCFS INIT 标志，仅当服务器在初始用户命名空间以 CAP_SYS_ADMIN 权限打开 /dev/fuse 时（挂载时用 file_ns_capable() 检查）才生效，即直接检查打开者权限而非推断挂载类型。补丁1为内核改动（UAPI 标志+权限限制），补丁2为基于原始 FUSE 协议的自测。已构建启动测试，三个用例均通过。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### coredump: select memory types per request
- https://lore.kernel.org/all/20260821-work-coredump-filter-v1-0-91f9a73ef03e@kernel.org/
- 该补丁系列让 coredump 服务器能按请求动态选择转储的内存类型。此前仅靠静态的 /proc/<pid>/coredump_filter 决定，服务器难以灵活配置。新增 COREDUMP_MEMORY_TYPES 特性位：若服务器设置该位，内核将转储 coredump_ack->memory_types 中指定的类型，零值也合法（仅含程序头和 notes）。coredump_req 新增 @memory_types（默认类型）和 @memory_types_mask（内核已知全部类型），服务器只能在掩码允许范围内设置。该特性需要 COREDUMP_KERNEL 及至少 VER1 大小的 ack。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### perf/KVM: Support PMU partitioning for x86 platforms
- https://lore.kernel.org/kvm/20260821222002.54907-1-zide.chen@intel.com/
- 该补丁系列为 x86 平台实现 PMU 分区，让 VMM 可将部分 PMU 资源分配给 guest，其余保留给 host，实现 host/guest 并发使用 PMU。它基于 Intel PerfMon masking（VMX 扩展，通过新 VMCS 字段 PERFMON_MASK 硬件强制隔离），构建于中介 vPMU 之上。KVM 新增 perfmon_mask 模块参数定义分区；perf 核心与 perf/x86 调度器遵守该掩码；PMI 仍走 host NMI 处理，host/guest 溢出分别处理。共23个补丁，涵盖 perf/x86、perf 核心、KVM 及自测，首发平台为 Diamond Rapids。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### arm64: expose CPU prefetch and cache modulation controls
- https://lore.kernel.org/all/20260817014943.10-1-kobak@nvidia.com/
- 该系列（RFC v6）新增 CONFIG_ARM64_CPUMOD，一个默认关闭的 arm64 接口，用于对 NVIDIA Grace/Vera CPU 的部分实现自定义预取和缓存管理字段做受控性能评估。它在 /sys/.../cpuN/cpumod/ 下暴露每 CPU 命名属性，写入前做范围校验，仅对 MIDR 匹配的 CPU 创建，支持热插拔动态增删，寄存器访问在对应 CPU 上执行。需固件允许 EL1 访问相关寄存器。已通过编译和静态验证，未做实机运行测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### vfio/pci: Add CXL Type-2 device passthrough support
- https://lore.kernel.org/all/20260813093631.2288172-1-mhonap@nvidia.com/
- 该系列（v4，27个补丁）为 CXL Type-2 加速器新增 VFIO 直通支持：客户机操作自己的虚拟 HDM 解码器并可复位设备，主机掌控物理解码器和主机物理地址，客户机仅选客户机物理地址，面向单一非交织端点解码器。相比 v3，寄存器模拟从 cxl-core 移入独立的 vfio-cxl 模块（vfio-pci 按需加载），cxl-core 仅保留复位入口。补丁覆盖 CXL 核心、VFIO-CXL 引导、HDM 区域虚拟化、DVSEC 复位、CXL 退出开关及文档测试。已通过编译和静态检查，但实机 ATS 路径需临时补丁。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### xswap: extendable (virtual) swap device backed by zswap
- https://lore.kernel.org/all/20260813104857.3450386-1-hebaoquan@kylinos.cn/
- xswap（RFC v3，15个补丁）是一个无后端存储的可扩展交换设备：换出页仅存于 zswap，不占磁盘，大小独立于物理设备。它用稀疏 vmalloc（VM_SPARSE）承载 cluster_info，按需增长/收缩，每设备上限可通过 debugfs 运行时调整。通过 /sys/kernel/mm/xswap/ 的 create/destroy 创建销毁设备（v3 改为真正无文件的 sysfs 接口）。因无后端，跳过物理写出并禁用 zswap 回写，故依赖 zswap，缺失时拒绝创建。本系列仅搭建基础框架，测试涵盖创建销毁与增减，均通过。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### cpunoise (CPU isolation testing tool) v0.2
- https://lore.kernel.org/all/20260815083728.15470-1-marco.crivellari@suse.com/
- cpunoise（v0.2）是 Marco Crivellari 与 Frederic Weisbecker 开发的用户态工具，用于测试、验证和调试 CPU 隔离与 NOHZ_FULL 工作负载配置，是 osnoise 的补充。它自动检查主机的 NOHZ_FULL、isolcpus、cgroup 等隔离配置，并通过 user_loop 假负载绑定到各 NOHZ CPU、采集解析 trace，过滤出隔离 CPU 上的意外干扰（定时器、工作队列、中断等）。也可单独用 noise_parse 解析 trace。作者征集反馈，希望了解需支持的 trace 事件、噪声源和配置边界情况。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### coredump: allow to create sparse coredumps on the coredump socket
- https://lore.kernel.org/all/20260811-work-coredump-sparse-v1-0-cd3e8b1e356d@kernel.org/
- 该补丁系列为通过coredump socket生成的核心转储引入稀疏（sparse）支持。当前若映射中含有空洞，仍会传输大量零数据，对映射大量内存的大进程而言浪费严重。作者不认同用coredump_filter解决（该掩码本意是选择包含哪类内存并跨fork/exec传播，而此处需要的是编码机制）。方案是：若服务端在coredump_ack->mask中置位COREDUMP_HEADER，则核心转储以帧序列（struct coredump_frame_header加数据）形式发送；再置位COREDUMP_SPARSE时，未填充映射发送零帧，仅标明需写入的零字节数而不含数据，重组后得到相同的核心文件，调试器等外部工具无需改动。测试显示效果显著：128线程进程约1GB转储仅传输1.7MB，且帧开销不足1%。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Introduce tiered memcg limits
- https://lore.kernel.org/all/20260807202059.2620949-1-joshua.hahnjy@gmail.com/
- 该RFC v3引入"分层memcg限制"，解决多工作负载共享分层内存（如DRAM、CXL、HBM等）系统上无法公平分配内存放置的问题。现有memory.{max,high}只限制总量，不管内存位于哪一层，导致先启动的工作负载独占快速层。该机制将memory.{min,low,high,max}按各层容量占比拆分到各内存层，并通过分配时引导、charge时定向回收、后台回收、迁移时charge及提升限速五种方式强制执行。功能通过启动参数"cgroup.memory=tiered_limits"启用，仅支持cgroup v2，默认无性能影响。测试显示分层后各工作负载的DRAM/CXL用量偏差大幅降低（最大/最小比从7.1倍降至1.06倍），任务完成时间的极差减少52%，代价是平均吞吐略降。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### virtio: support devices that own their virtqueue memory
- https://lore.kernel.org/all/20260809182010.32931-1-graf@amazon.com
- 该RFC提出对virtio的扩展DMB（设备内存缓冲区），让每个virtio设备拥有专属的、与主机通信的内存区域，而非直接映射整个guest内存。此举可提升机密计算和隔离vhost-user后端设备的安全性——设备只能看到DMB区域而非全部guest RAM。所有原本指向guest RAM的偏移改为指向该共享缓冲区，且该机制位于virtio传输层，上层驱动无需修改。相比swiotlb方案，DMB与操作系统无关（利于Windows支持）、提供独立DMA空间、支持设备按需选用。当前限制：仅支持PCI，特性位44等尚未获OASIS正式分配。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### arm-mpam: Add basic device tree support for resctrl
- https://lore.kernel.org/all/20260811-mpam-resctrl-dt-knp-support-v1-0-ea6397bead59@oss.qualcomm.com/
- 该RFC补丁系列为Arm MPAM（内存系统资源分区与监控）的resctrl添加基础设备树（DT）支持，这是启用更高层功能（如MPAM固件支持分区MPAM-FB）的前提。补丁基于James Morse、Shanker Donthineni和Rob Herring尚未上游的工作，保留原作者署名，并将修复以独立小补丁形式叠加以便审查。DT亲和性模型将MSC节点嵌套在其分区/监控的设备下：缓存MSC从父缓存节点派生CPU亲和性，内存控制器MSC则对所有CPU可访问，并提供基于per-RIS的回退方案。Kaanapali DTS补丁仅供本地验证、无法上游。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Page Alloc Hogger
- https://lore.kernel.org/all/20260806011048.517229-1-jyescas@google.com
- 该RFC v2引入"Page Alloc Hogger"工具，允许通过debugfs直接从指定的节点、内存区（zone）、迁移类型和阶（order）分配内存页。其主要用途包括：复现低内存条件以检验直接回收、kswapd、OOM killer及分配回退等内核机制；简化内存压力调试，无需自定义驱动或用户程序；简化单元测试；以及测量应用在压力下的性能。使用时向对应debugfs路径的nr_pages_allocs写入分配数量，每次分配生成一个序号文件，向free文件写入序号即可释放。目前除ZONE_DEVICE外均支持，MIGRATE_CMA即将支持。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### arm64: Support for Arm CCA in KVM
- https://lore.kernel.org/all/20260803134403.80630-1-steven.price@arm.com/
- 本补丁集为arm64 KVM增加Arm CCA支持，可创建、填充并运行受保护的Realm虚拟机，同时加入RMM通信固件层。v16重新合并固件与KVM补丁，重构虚机进出、定时器及SRO流程，强化错误处理和内存检查，并预计兼容RMM 2.0 Beta3。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Introduce region-aware RDT support
- https://lore.kernel.org/all/cover.1785680802.git.yu.c.chen@intel.com
- 该RFC概念验证补丁为Intel平台引入区域感知RDT，面向DDR、CXL等内存层级，按区域独立监控和限制带宽。其扩展resctrl，增加分区域MBM统计文件和MBA控制项，依赖多控制器框架，当前仅供试用讨论，尚不适合合入上游。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add support for multiple versions to KHO
- https://lore.kernel.org/all/20260731215224.831696-1-loganodell@google.com
- 该RFC为KHO新增多版本数据保存接口，允许LUO在同一子树节点下按版本存放不同格式的数据，以兼容新增功能及内核差异；同时支持混合模式，确保回滚至旧内核仍可读取。补丁还重构节点保存逻辑，扩展debugfs，并新增测试用例。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### famfs: the Fabric-Attached Memory File System (standalone)
- https://lore.kernel.org/all/0100019fc572ca94-ec363dd7-3a77-484b-b4b7-f2503a0931a6-000000@email.amazonses.com/
- 该补丁集将famfs恢复为独立文件系统，用于把超大规模共享、解耦内存以文件形式提供字节级访问和直接映射。它基于fsdev模式DAX设备，不使用页缓存，可由多节点挂载，并通过缓存映射元数据降低缺页开销，满足内存级性能需求。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add buffered write-through support to iomap & xfs
- https://lore.kernel.org/all/cover.1785908600.git.ojaswin@linux.ibm.com
- 该RFC为iomap与XFS引入缓冲直写，数据复制到页缓存后立即落盘，仅完整提交部分视为成功。新版细化短写及错误语义，引入NOSERIAL共享锁，减少脏页与回写开销。测试显示，多写者随机覆盖性能显著提升，追加写基本持平。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: optimize zone-device memmap initialization
- https://lore.kernel.org/all/20260803070929.86075-1-lizhe.67@bytedance.com
- 该补丁集优化ZONE_DEVICE内存映射初始化，通过复用struct page模板批量复制，避免逐页重复设置；x86进一步采用非时序拷贝，其他架构回退至普通复制。测试显示，大容量PMEM、DAX及设备私有内存初始化耗时普遍降低约五至六成。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2026年 第07期 (Start From 2026/07/01)

#### arm64: crash: Add crash hotplug support
- https://lore.kernel.org/all/20260723131242.1537633-1-ruanjinjie@huawei.com
- 该补丁集为 arm64 引入 kdump 崩溃热插拔支持，在 CPU 或内存热插拔时仅更新 elfcorehdr，避免用户态重载整个镜像及长时间停用。同时修复 powerpc 和 arm64 的内存泄漏、空指针及内存区间截断问题，并简化相关加载流程。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched, steal_governor: Introduce preferred CPUs and steal-driven vCPU backoff
- https://lore.kernel.org/all/20260724140732.2683314-1-sshegde@linux.ibm.com
- 该补丁集引入“首选CPU”调度机制与steal_governor模块，以窃取时间衡量虚拟化环境的物理CPU争用。高争用时逐步减少首选vCPU并聚合负载，低争用时自动恢复，在遵守任务亲和性的同时降低抢占开销、提升整体吞吐量。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Neural Storage Driver 
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认
#### learning page cache prefetcher
- https://lore.kernel.org/all/20260725182628.221603-1-nsd.project.dev@gmail.com
- 该RFC提出神经存储驱动NSD，通过监控文件读取，以马尔可夫链学习4KB区域访问模式并预测预取。测试显示预取命中率达98%，可提升SQLite查询和顺序读取性能，随机读取无明显退化，并探讨是否应与现有预读状态深度集成。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add reclaim to the dmem cgroup controller
- https://lore.kernel.org/all/20260723100350.16895-1-thomas.hellstrom@linux.intel.com
- 该补丁集为设备内存控制器增加同步回收能力：下调上限时尝试回收显存，失败返回忙碌错误；新增可扩展注册及回调接口，并接入TTM、xe和amdgpu，同时修复初始化、并发注销、错误路径及驱动卸载中的泄漏与释放后使用问题。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### fuse: allow parallel direct writes for passthrough
- https://lore.kernel.org/all/20260726015955.319132-1-russ.fellows@gmail.com/
- 该补丁允许FUSE透传模式下符合条件的直接覆盖写共享inode锁，保留并复用并行写标志及锁逻辑，消除写入串行化。测试未发现回归或内核告警，四任务随机写性能由约42万提升至99万IOPS，单任务及读取性能不变。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### XFS: Atomic multi-extent operations via rolling transactions
- https://lore.kernel.org/all/20260729100629.1943710-1-dgc@kernel.org/
- 该33项RFC补丁通过滚动事务，使XFS多区段映射、延迟分配、未写转换及COW操作在ILOCK下原子完成，消除竞态与数据损坏风险；新增块预留重授机制以安全处理空间不足，并修复事务取消、文件大小更新和预留错误。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm, swap: dynamic cluster management for xswap devices
- https://lore.kernel.org/all/20260727135029.1059441-1-baoquan.he@linux.dev/
- 该RFC为仅由zswap支撑、暂无回写的xswap设备实现动态簇管理，以4K磁盘头声明容量，免除完整后端存储。簇数组采用稀疏虚拟内存按需扩缩并保持常数时间索引，支持运行时调整上限，为后续回写、反向映射等功能奠定基础。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### nvme-tcp: NIC topology aware I/O queue scaling and queue info export
- https://lore.kernel.org/all/20260727151315.3658708-1-nilay@linux.ibm.com
- 该补丁使NVMe/TCP按网卡收发队列数扩展I/O队列，并结合中断亲和性改善CPU局部性；同时通过debugfs导出队列、CPU及TCP流信息，便于配置中断和流量导向。测试显示无性能回退，调优后吞吐最高提升约二点五倍。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### net: knod: in-kernel network offload device
- https://lore.kernel.org/all/20260719175857.4071636-1-ap420073@gmail.com/
- 该RFC提出knod（内核网络卸载设备），直接从Linux内核驱动GPU来加速数据包处理，数据路径无需CUDA/ROCm等用户空间GPU运行时。内核自行分配GPU队列、将每包程序JIT编译为GPU机器码并调度，网卡通过DMA将数据包直接送入GPU内存，GPU并行处理后返回裁决（PASS/DROP/TX），仅PASS包经GPU的DMA引擎拷贝至主机。它利用GPU的SIMT特性匹配XDP每包处理模型，将L4负载均衡、IPsec加密等计算从CPU卸载到GPU，透明支持现有XDP程序和IPsec SA。框架分为中立核心与AMD GPU provider，通过netlink控制。当前展示BPF和IPsec（仅RX、概念验证）两个特性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add the the capability to load HW RX checksum in eBPF programs
- https://lore.kernel.org/all/20260715-bpf-xdp-meta-rxcksum-v5-0-623d5c0d0ab7@kernel.org/
- 该补丁系列v5引入bpf_xdp_metadata_rx_checksum() kfunc，使绑定到网卡的eBPF程序能够读取硬件RX校验和结果，并为veth和ice驱动实现了xmo_rx_checksum回调。若硬件检测到错误或失败的校验和，或无法解析数据包（如不支持特定协议），元数据中将报告CHECKSUM_NONE。一个可能的应用场景是结合该kfunc与bpf_xdp_metadata_rx_hash()的信息，实现XDP DDoS防护应用，用于过滤校验和错误的数据包。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Private Memory NUMA Nodes
- https://lore.kernel.org/all/20260720193431.3841992-1-gourry@gourry.net/
- 该补丁系列v5引入"私有内存节点"概念，默认只保留页分配和OOM杀两项基本功能，其余mm/服务通过能力位（CAPS）显式opt-in。核心目标是将NUMA内存 从"默认全可访问"翻转为"默认隔离、按需开放"。隔离通过专用zonelist实现：私有节点不出现在FALLBACK列表，只在ZONELIST_PRIVATE中可见，配合MPOL_F_PRIVATE经mempolicy访问，避免现有代码误分配。能力位包括RECLAIM、USER_NUMA、DEMOTION、HOTUNPLUG、NUMA_BALANCING、LTPIN等。适用于GPU、压缩内存、分层内存等场景，首个内核用户为KVM。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Arm Core Local Accelerator Driver
- https://lore.kernel.org/all/20260717104759.123203-1-ryan.roberts@arm.com/
- 此RFC引入Arm核心本地加速器（CLA）驱动，这是一种用于编程连接加速器的CPU本地接口。接口不限加速器类型，当前目标为计算引擎（CLA非Arm架构组成部分）。当前范围限于裸机支持，虚拟化将另发RFC。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### tracing/osnoise: Track IPIs
- https://lore.kernel.org/all/20260715154553.2020891-1-vschneid@redhat.com/
- 此补丁系列v3为osnoise跟踪工具添加IPI（处理器间中断）追踪功能。作者发现IPI引发的延迟尖峰常因隔离配置错误导致，通常在长时间（如24小时）timerlat运行末尾才被发现。这些IPI并非罕见，而是单独不足以触发延迟阈值，往往是多重干扰叠加才导致问题。为便于检测此类配置错误及命中隔离CPU的IPI，作者最初曾修改timerlat，但Tomáš认为不合适。故改为在osnoise中实现IPI追踪，且完全在用户空间完成，便于部署到旧内核。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### pidfd: add a minimal process spawn builder
- https://lore.kernel.org/all/cover.1784204592.git.me@linux.beauty
- 此RFC提出为pidfd添加最小化进程创建构建器，借鉴fsconfig()设计，让用户空间可实现posix_spawn()。通过pidfd_open创建无任务的future pidfd，再由pidfd_spawn_run创建实际任务和PID。支持基于源进程的模式，运行时采样调用者的cwd、umask、fd表等状态，并支持DUP2、CLOSE_RANGE、FCHDIR等有序文件操作。内部仍使用CLONE_VM|CLONE_VFORK加exec实现。作者探讨了seccomp、审计、LSM等安全问题，未来计划补全posix_spawn语义、支持纯净进程构建及PATH查找等功能。当前UAPI刻意精简，以便优先审查状态模型和内核/用户空间边界。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Support the FEAT_HDBSS introduced in Armv9.5
- https://lore.kernel.org/all/20260709104026.2612599-1-zhengtian10@huawei.com/
- 该系列为Armv9.5引入的HDBSS（硬件脏状态跟踪结构）特性添加支持。HDBSS利用硬件辅助实现脏页跟踪，相比现有的写保护或扫描stage-2页表方式，能显著降低脏页扫描开销，从而减少热迁移对客户机和宿主机的执行开销。补丁使内核在任一memslot启用脏日志时自动开启HDBSS，全部禁用时关闭，暂不支持dirty ring模式。v4在stage-2 MMU初始化时将DBM注入pgt->flags，首次脏访问不再触发缺页，故强制依赖Leonardo的补丁以确保HDBSS可用时启用急切大页拆分，避免迁移后客户机挂起。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### arm64: Add support for FEAT_NMI
- https://lore.kernel.org/all/20260709121333.23507-1-vladimir.murzin@arm.com/
- 该RFC系列为arm64添加FEAT_NMI支持，这是一种支持不可屏蔽中断(NMI)及低屏蔽中断(LMI)的架构机制。由于已通过优先级屏蔽支持伪NMI，直接叠加新机制易使代码混乱，故系列先重构现有异常屏蔽逻辑：将异常状态的逻辑视图与硬件表示分离，引入可映射到硬件状态的逻辑异常上下文，把硬件相关处理集中到少数位置。因重构复杂且可能引入细微行为变化，还添加了大量调试检查以验证硬件与逻辑状态一致。作者致谢多位贡献者，希望获得方案反馈及真实硬件测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add support for AMD IOMMU GAPPI
- https://lore.kernel.org/all/20260713105033.15405-1-sarunkod@amd.com
- 该系列为AMD IOMMU新增GAPPI支持，作为AVIC/x2AVIC客户机中断重映射在vCPU未运行时的替代宿主通知路径。传统GALOG将所有唤醒集中于单一日志与中断，重负载下延迟高且易溢出；GAPPI则直接向IRTE[Destination]投递物理APIC中断，将唤醒分散到各CPU。前四个补丁重构SVM/IOMMU接口（cpu改名apicid、ga_log_intr改wakeup_intr、新增is_running布尔）。KVM沿用Intel posted-interrupt唤醒模型，每pCPU维护阻塞vCPU列表。GAPPI经amd_iommu=gappi启动参数启用，否则保持原有路径。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### io_uring: prototype for device memory tx
- https://lore.kernel.org/all/cover.1783614400.git.asml.silence@gmail.com/
- 该RFC为io_uring的IORING_OP_SEND[MSG]_ZC提供设备内存发送(tx)的初步原型，主要用于测试而非展示设计（作者对uapi及依赖zcrx不满意，将重做）。它依附于zcrx实例，复用其rx队列管理、设备通信及内存映射。因缺乏传递netmem的迭代器类型，改用ubuf/iovec迭代器并借助新的sg_from_iter构建skb。类似devmem TCP，通过引用实现{get,put}_netmem，并在validate_xmit_unreadable_skb()中校验skb发往正确设备。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: PMD-level swap entries for anonymous THPs
- https://lore.kernel.org/all/20260713133613.2707815-1-usama.arif@linux.dev
- 该系列引入PMD级swap条目，使匿名THP在换出时无需拆分为HPAGE_PMD_NR个PTE级条目，换入时可直接恢复PMD映射，避免依赖khugepaged后续合并。PMD swap条目紧凑编码连续swap槽，swap_map仍按槽计账。当swap缓存出现拆分/逐页状态或zswap逐页存储时，则拆分回退至PTE路径。补丁按序确保所有消费者（fork、zap、mincore、swapoff、缺页、UFFDIO_MOVE等）先支持PMD条目，换出生产者最后启用。zswap原生PMD支持留待后续。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Simplify special kernel page table handling
- https://lore.kernel.org/all/20260714-remove_pgtable_cdtor-v1-0-44be8a7685d7@arm.com
- 这组补丁旨在简化内核特殊页表处理。页表构造/析构函数原为用户PTE页设计，后扩展至各层级，但vmemmap等特殊内核页表仍未调用。作者发现内核页表根本不需要ctor/dtor，遂将通用逻辑移至pagetable_{alloc,free}()，ctor/dtor仅保留给用户页表（PTE/PMD层级）。补丁引入"kernel mm"概念替代&init_mm比较，标记efi_mm等特殊mm为内核mm（不再用分离页表锁），并移除arm/arm64/riscv上的相关调用。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### skb extension for BPF metadata
- https://lore.kernel.org/all/20260714-bpf-meta-inside-skb-ext-v1-0-5871c07a8dd6@cloudflare.com/
- 本系列补丁为 BPF 程序引入一种按数据包传递元数据的机制。当前网络栈不同挂载点的 BPF 程序无法互相传递每包数据，XDP 的 data_meta 仅覆盖 XDP 到 TC 阶段。方案通过新增 skb 扩展（bpf_skb_ext）内联存储元数据字节缓冲区，程序经 bpf_dynptr_from_skb_ext() 以 dynptr 访问。可选标志控制读写、创建及是否在隧道封装、跨网络命名空间转发时保留。缓冲区最大 256 字节，默认 64。此为第三次尝试，作为 Netdev 演讲配套 RFC 发布，性能测试结果待跟进。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### coco: guest: Enforce host page-size alignment for shared buffers
- https://lore.kernel.org/all/20260706060432.1375570-1-aneesh.kumar@kernel.org/
- 该系列（v5）为机密计算（CoCo）客户机与宿主机间的**共享缓冲区强制页大小对齐**。因宿主可能以大于客户机页（如 64K）的粒度管理共享/私有状态，仅共享 4K 子区间不安全，尤其 mmap 到用户态时易致 GPC 故障与内核崩溃。补丁要求共享缓冲区**地址对齐且大小为共享粒度整数倍**，新增通用助手 `mem_cc_shared_granule_size()` 等（默认 PAGE_SIZE，arm64 CCA 经 RHI 查询覆盖），并更新 set_memory_encrypted、GIC ITS、dma-direct、SWIOTLB、dma-buf 等分配路径。Hyper-V 路径不受影响。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Open HugeTLB allocation routine for more generic use
- https://lore.kernel.org/all/20260702-hugetlb-open-up-v4-0-d53cefcccf34@google.com/
- 该系列（v4）重构 HugeTLB 分配路径，使其能作为通用大页来源被更广泛使用，动机源于 guest_memfd——它希望借助 HugeTLB 提供大页，但不采用其在 mmap() 时的预留机制。原 `alloc_hugetlb_folio()` 强依赖 VMA（用于查预留 resv_map 和获取 mpol 内存策略）。补丁新增 `hugetlb_alloc_folio()`，仅专注分配本身及内存与 cgroup 计费，无需 VMA；`alloc_hugetlb_folio()` 仍处理预留与子池。此改动也简化了原本连 HugeTLBfs 都需用伪 VMA 的耦合。libhugetlbfs 及 selftest 测试通过。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### binfmt_misc: bpf-backed binary type handlers
- https://lore.kernel.org/all/20260707-work-bpf-binfmt_misc-v1-0-74b995c84ec1@kernel.org/
- 这是一个 POC（RFC），为 binfmt_misc 增加 **eBPF 支持的二进制类型处理器**，主要解决 Nix 风格可重定位、自包含二进制的动态加载器需相对自身路径确定的问题（PT_INTERP 和固定解释器字符串都无法表达）。此前的 $ORIGIN 扩展和可插拔 ELF 加载器方案均被否决。新方案通过 `binfmt_misc_ops` struct_ops，让 load 程序读取文件内容、解析 ELF、经 `bpf_path_d_path` 解析路径，并用新 kfunc `bpf_binprm_set_interp` 暂存绝对路径。以新 'B' 类型注册（`echo ':origin:B:nix::::'`），完全沿用现有权限与命名空间模型，仅使匹配可编程化。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: A common way to attach struct_ops to a cgroup
- https://lore.kernel.org/all/20260706171918.317102-1-ameryhung@gmail.com
- 该系列（bpf-next v3）延续 Martin 的工作，为 **struct_ops 附加到 cgroup 提供统一接口**。缘由是需替代不断扩充 `BPF_SOCK_OPS_*CB` 枚举来扩展 tcp_sock 操作，且附加时需可预测的顺序；2026 年又提出 OOM、memcg 等新用例。BPF 已有基于 bpf_link 的通用 cgroup 附加 API（含 attach/detach/update/排序/查询语义），本系列将该模型扩展到 struct_ops。首个用户为新的 `struct bpf_tcp_ops`（镜像 TCP sockops 钩子，故意排除 NEEDS_ECN 和 BASE_RTT）。selftest 覆盖附加、查询、更新、排序、前后放置、返回值链及多层级 cgroup 继承。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Short circuit delivery for coredump signals
- https://lore.kernel.org/all/877bnb4uyw.fsf_-_@email.froward.int.ebiederm.org
- 该系列（v2）为**触发核心转储（coredump）的信号实现短路投递**。受 Oleg 修改 force_sig_info 的启发，作者更新信号处理机制，让 coredump 不再是庞大的特殊情况——统一后一切更简单。难点在于 coredump 原有独立于内核其他机制的进程终止（shoot-down）逻辑；补丁主体即是**合并信号与 coredump 的进程终止逻辑**使其共享。Oleg 审阅时发现 `dequeue_exit_signal` 未正确处理触发 coredump 的线程本地信号，为此作者新增清理：在信号入队时检测致命信号并放入共享队列，并重写了信号能否立即投递（短路投递）的检测逻辑，增强对被忽略信号及导致进程退出信号（如 SIGKILL）的处理。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### nvme-rdma: parallelize I/O queue setup
- 	https://lore.kernel.org/all/20260627041551.1981256-1-sgogte@purestorage.com
- 该补丁系列（v4）旨在优化 nvme-rdma 的连接与重连速度，将 I / O 队列的建立由串行改为并行。它把每个队列的分配与启动合并为单个异步工作项，使各队列的连接延迟相互重叠，尤其利好高核数、多 I / O 队列的主机。补丁 1 为预备重构，补丁 2 为并行实现。在 64 核、64 队列的主机上测试，连接时间从约 1.4 秒降至 416 毫秒。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「nvme-rdma: parallelize I/O queue allocation and startup」）

#### Introduce MMIO-based CMT access for Enhanced RDT
- https://lore.kernel.org/all/cover.1782866200.git.yu.c.chen@intel.com
- Intel 增强型 RDT（ERDT）扩展了现有 RDT 框架，引入两大能力：基于 MMIO（替代传统 MSR）的监控与分配寄存器访问，以及面向不同内存层级（如 CXL.mem、DDR）的区域感知控制。本补丁集（v5）聚焦第一部分，为缓存监控技术（CMT）启用 MMIO 访问，平台通过 ACPI ERDT 表描述寄存器布局。借此，L3 缓存占用计数器可从任意 CPU 无需跨核 IPI 读取，并解析 RMDD、CMRC 子表以支持相关功能。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### vfio/pci: Add mmap() for DMABUFs
- https://lore.kernel.org/all/20260701171245.90111-1-matt@ozlabs.org/
- 该补丁系列（v4）为 vfio-pci 的 DMABUF 增加 mmap () 支持，使用户态驱动能将 PCI 设备 BAR 的子集导出为 DMABUF，通过 fd 分发给子进程，实现受限、可隔离的设备访问（优于共享整个设备 fd）。系列还将现有 BAR mmap () 统一改为基于 DMABUF 的公共 vm_ops 与缺页处理，并新增强制撤销机制、写合并等内存属性设置。同时拆分 P2PDMA 核心以适配 32 位等架构。已在多 BAR、大页、撤销等场景测试通过，无回归。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Introducte Reserved THP
- https://lore.kernel.org/all/cover.1782538002.git.zhengqi.arch@bytedance.com/
- 该 RFC 提出 "Reserved THP"（可预留的透明大页），旨在融合 HugeTLB 与 THP 的优点，作为统一二者的起点。它兼具 HugeTLB 的预留保证与 THP 的 swap 等 mm 核心集成能力。实现上新增 MIGRATE_RESERVED_THP 迁移类型、启动参数及 MADV_RESERVED_THP，预留内存仅能经 madvise 消费。动机源于热升级场景中大量 HugeTLB 内存被浪费。未来计划支持大页整体换入换出、纳入回收路径、作为 tmpfs / hugetlbfs 后端、1GB 大页，最终移除 HugeTLB。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Accelerate page migration with batch copying and hardware offload
- https://lore.kernel.org/all/20260630-shivank-batch-migrate-offload-v6-0-da95d7e8b8a2@amd.com/
- 该 RFC（v6）通过批量复制页面并支持 DMA 硬件卸载来加速页面迁移，解决单线程逐个 folio 复制的瓶颈（尤其大 folio）。它构建批量复制框架，提供 DMA 卸载参考驱动 dcbm，并支持可插拔迁移器。复制完成的 folio 标记 FOLIO_CONTENT_COPIED，失败则回退 CPU 逐个复制。在 AMD EPYC 上测试，2M folio 用 16 DMA 通道吞吐从 10.
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/vmpressure: reduce CPU, memory and code overhead on cgroup v2
- https://lore.kernel.org/all/20260630112617.1198623-1-usama.arif@linux.dev
- 该补丁系列（v3）优化 vmpressure 子系统在 cgroup v2 上的开销。vmpressure 有两类消费者：内核 socket 压力（tree = false，v2 用）与 v1 用户态 eventfd 通知（tree = true，v2 无对应）。补丁 1 扩展提前返回，跳过 v2 + tree = true 的无用路径，消除 sr_lock 竞争（生产机每分钟约 1.6 万次调用）。补丁 2 将 v1 专用代码拆分至 memcontrol-v1.c，使 vmpressure.c 减半，并节省内存（结构体缩减），为最终将 vmpressure 变为 v1 专属铺路。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### seccomp: non-cooperative pinned-memfd argument redirect
- https://lore.kernel.org/all/20260627012219.1079851-1-xiyou.wangcong@gmail.com/
- 该补丁系列（v4）解决 seccomp 用户通知中 CONTINUE 响应的 TOCTOU 竞态：监督进程放行系统调用后，目标可篡改指针参数所指内存。方案无需目标配合：内核将监督者拥有的只读、写封印、VM_SEALED 的 memfd 映射（PIN）装入目标进程，再用 SEND_REDIRECT 重写参数寄存器指向该不可变缓冲区，使目标无法赢得竞态。重定向的系统调用会重新经外层过滤器校验，防止绕过策略；execve 作特殊处理。可用于非合作沙箱 sandlock 实施参数级策略。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: apply chainsaw to struct kvm_mmu
- https://lore.kernel.org/all/20260624213102.71082-1-pbonzini@redhat.com
- 该系列（v2）重构 KVM 中臃肿的 "上帝结构体" kvm_mmu（原混合了描述客户机页表格式、遍历页表、构建页表三种职责），将其拆分为三部分：kvm_pagewalk（页表遍历器，每 vCPU 两个：gva_walk 与 ngpa_walk）、kvm_mmu（保留影子页表构建功能）、kvm_page_format（操作已存在的 PTE，合并权限掩码与保留位校验）。清理消除了 guest_mmu 与 nested_mmu 的命名混淆。末补丁复用 permission_fault 机制校验 SPTE，使支持 XS≠XU 的 SPTE（可经内存属性添加新特性）。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2026年 第06期 (Start From 2026/06/01)

#### lib: Rust implementation of SPDM
- https://lore.kernel.org/all/20260623045406.2589547-1-alistair.francis@wdc.com/
- 该补丁系列用 Rust 实现 SPDM（安全协议与数据模型）请求方。SPDM 用于设备认证、证明与密钥交换，内核视设备为不可信，需解析复杂规范（近 250 页）的不可信响应，存在漏洞风险，正适合 Rust。该系列基于 Lukas 的 C 实现重构，目标是先上游最小可用的 SPDM 实现，仅支持与设备通信并返回"已认证"，暂不提供证据/证书、自定义 nonce、PQC 等高级功能。它将 PCI-CMA 作为 TSM 驱动加入，便于 PCIe 复用 TSM；其他传输（ATA、SCSI、NVMe、MCTP）需另加 netlink/sysfs 封装。已在 QEMU 中测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/vmalloc: Speed up ioremap, vmalloc and vmap with contiguous memory
- https://lore.kernel.org/all/20260618084726.1070022-1-jiangwen6@xiaomi.com
- 该补丁系列在物理内存完全或部分连续时加速 ioremap、vmalloc 和 vmap，采用两种技术：为多段内存设置 PTE/PMD 时避免重复遍历页表，以及在 vmalloc 和 ARM64 层尽可能使用批量映射。它还为 vmap 启用了当前不支持的大映射（PMD 和 cont-PTE）。在 RK3588 上，ioremap 提速 1.35 倍、vmalloc 1.42 倍、vmap 达 8.3 倍。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/page_owner: add per-fd filter infrastructure for print_mode and NUMA filtering
- https://lore.kernel.org/all/20260618035750.3724613-1-zhen.ni@easystack.cn/
- 该补丁系列为 page_owner 引入按文件描述符（per-fd）的过滤功能。在大内存（250GB+）生产环境中，page_owner 输出文件常达数 GB 至 10GB+，造成存储与传输压力，主因是冗余的栈回溯信息。系列提供两类过滤器：打印模式过滤器（只输出栈句柄而非完整栈，大幅缩减体积）和 NUMA 节点过滤器（按节点列表筛选，支持单值、多值、范围）。per-fd 设计支持多用户并发使用不同过滤器。包含 4 个补丁：print_mode 基础设施、NUMA 过滤、用户态工具及文档，并在 4 节点 NUMA 系统经 26 个测试用例验证。未来可扩展 PID、时间范围等过滤。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### liveupdate: kvm: guest_memfd preservation
- https://lore.kernel.org/all/20260622184851.2309827-1-tarunsahu@google.com
- 该非 RFC 补丁系列实现 guest_memfd 的保活（liveupdate 跨 kexec 保留）。经多次跨 hypervisor liveupdate、guest_memfd 双周会讨论后，确定了基础支持设计。本系列覆盖完全共享、不支持私有内存、由 PAGE_SIZE 页支撑的 guest_memfd。测试步骤为：以 CONFIG_LIVEUPDATE_GUEST_MEMFD=y 编译内核，启动时加 kho=on liveupdate=on 参数，分两阶段（kexec 前后）运行 kselftest，并验证 kvm_vm_luo 与 guest_memfd_luo 处理程序已注册。代码基于 kvm/next 加 liveupdate/next 及若干前置补丁。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Support memory hotplug/unplug for TDX CoCo guests
- https://lore.kernel.org/all/20260623101739.79695-1-zhenzhong.duan@intel.com
- 该 RFCv2 系列为 Intel TDX 机密计算客户机实现 virtio-mem 与 ACPI DIMM 内存热插拔/拔出的完整支持，采用基于原生 TDG.MEM.PAGE.RELEASE API 的 start-private 内存方案。相比 v1，取消了回调机制改用平台级 unaccept 函数、新增"plugged"位图以支持 load_unaligned_zeropad()、并增强 EFI stub 早期解析 SRAT 表。技术上通过早期 SRAT 解析识别可热插拔范围、双位图跟踪已填充内存、暴露通用 CoCo 接口供 SEV-SNP 等复用、拔出时显式置内存为"未接受"状态、并支持 kexec 跨界传递位图。已测试 DIMM 与 virtio-mem 热插拔、惰性/急切接受及 kexec/kdump。作者寻求 CoCo、MM 及 virtio 社区反馈，暂不需 x86 维护者审查。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: guest_memfd: folio migration for non-confidential VMs
- https://lore.kernel.org/all/20260611-shivank-gmem-migrate-v1-0-2d266bfc6f95@amd.com/
- 该 RFC 系列为非机密虚拟机（如 Firecracker）的 guest_memfd 启用页（folio）迁移功能。当前 guest_memfd 的 folio 被标记为不可迁移，导致内核无法进行 NUMA 平衡、内存压缩等操作；这对加密内存的机密虚拟机（SEV-SNP、TDX）是必须的，但非机密虚拟机本可迁移。本系列实现非机密 guest_memfd 的迁移，并为将来机密虚拟机迁移（待固件辅助拷贝支持，用 FOLIO_CONTENT_COPIED 跳过主机侧拷贝）打基础。已通过 KVM selftest 与 Firecracker 测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### tcp: opportunistic loopback splice for BPF-paired sockets
- https://lore.kernel.org/all/20260612011452.134466-1-xiyou.wangcong@gmail.com/
- 该 RFC 系列为 BPF 配对的本地 TCP 套接字增加"环回拼接（loopback splice）"快速路径。当 sock_ops BPF 程序在握手完成时将两个本地互连的 TCP 套接字配对后，sendmsg 直接把数据拷入内核字节环、recvmsg 从另一侧取出，绕过 skb 构造、软中断和 TCP 协议处理。底层 TCP 连接仍真实存在（序列号冻结），FIN/RST/keepalive 正常走原路径，且按消息可回退。适用于同主机进程及容器 sidecar 场景，应用无需改动。在 TCP_RR 1KB 测试中提速约 2.2 倍，配合 busy-poll 达 6.7 倍。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kmem_cache instances with static storage duration
- https://lore.kernel.org/all/20260611171425.1671254-1-viro@zeniv.linux.org.uk
- 该补丁系列引入具有静态存储期的 kmem_cache 实例。当前 kmem_cache_create() 返回指针，热点路径解引用该指针会拖累性能；之前用 runtime_const 优化但依赖架构、且大多架构不支持。本方案对"从不销毁"的缓存采用静态实例（用与 kmem_cache 同大小对齐的 kmem_cache_opaque 透明类型），直接用取地址 & 替代指针解引用，性能不亚于 runtime_const，且支持模块。难点在于模块中创建的缓存需在卸载前正确释放并处理 sysfs 引用，通过持有 module kobject 引用解决。代价是新增 SLAB_PREALLOCATED 标志、此类缓存不可合并。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched: Add support for long task name
- https://lore.kernel.org/all/20260612-tonyk-long_name-v3-0-7989b66e8a99@igalia.com
- 该补丁系列为内核增加长任务名支持。调试含数百线程的复杂程序时，现有 16 字节的线程名（TASK_COMM_LEN）已不够用。本系列新增 PR_{SET,GET}_EXT_NAME，支持 64 字节长名称，并将 current->comm 扩展至 TASK_COMM_EXT_LEN，同时确保现有用户态 API 仍只返回 16 字节。还引入 copy_task_comm() 函数保证字符串始终 NUL 结尾（不用 strscpy 因其有追踪开销）。补丁含防缓冲区溢出的预备工作、KUnit 测试及 selftest 适配。基准测试显示开销仅增加约 0.7%。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Support virtio-mem memory hotplug in TDX guests
- https://lore.kernel.org/all/20260604093551.1511079-1-zhenzhong.duan@intel.com
- 该 RFC 系列探索在 TDX 等机密计算（CoCo）客户机中支持 virtio-mem 内存热插拔。它采用"start-private"私有内存方案，通过基于回调的机制实现子块粒度的内存接受（PAGE.ACCEPT）与释放（PAGE.RELEASE），解决以往方案在粒度不匹配、重复接受报错等问题。出错时将设备标记为 broken 以保证稳定性。已通过热插拔及 kexec/kdump 测试，但暂不支持惰性接受（lazy accept），旨在征求社区反馈。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### nvdimm: virtio_pmem: fix request lifetime and converge broken queue failures
- https://lore.kernel.org/all/20260609120726.1714780-1-me@linux.beauty
- 该补丁系列修复 nvdimm/virtio-pmem 的两类问题。其一，nvdimm_flush() 将提供者的具体错误统一转成 -EIO，掩盖了如 -ENOMEM 等有用信息，故改为直接返回原始错误，并将子 flush bio 分配改用 GFP_NOIO，解决 mkfs 报 I/O 错误的问题。其二，修复请求生命周期与坏队列处理：通过引用计数避免完成处理时的释放后使用（UAF），唤醒所有等待者，将坏队列收敛为 -EIO，并在 freeze 时排空请求，防止无限期睡眠。已在 QEMU x86_64 测试通过。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「nvdimm: virtio_pmem: converge broken virtqueue to -EIO」）

#### Bootpatch-SLR: Randomizing Linux Kernel Structure Layouts at Boot
- https://lore.kernel.org/all/20260605202511.79272-1-yjn@yjn-systems.com
- 该 RFC 提出 Bootpatch-SLR（BPSLR），一个在 Linux 内核启动时（而非编译时）对结构体布局进行随机化的研究项目，由慕尼黑工大硕士生开发。其核心思想是让单一内核镜像在每次启动时随机化字段偏移，从而对抗"一次构建分发到百万系统、布局一旦泄露则全部已知"的问题。它通过 GCC 插件记录结构访问，启动早期直接改写访问指令而无需查表。当前原型基于 v6.12，仅随机化 task_struct（x86_64），引导开销小于 1 秒，作者征求关于布局假设的反馈。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### GiantVM based on shared memory
- https://lore.kernel.org/all/20260605093857.747735-1-muliang.shou@sjtu.edu.cn/
- 该补丁来自上海交大，介绍 GiantVM——一个基于 QEMU/KVM 的"多对一"虚拟化框架。它利用分布式共享内存（DSM）将多台普通服务器聚合为一台逻辑大虚拟机，在 scale-up 与 scale-out 间取得平衡，且无需修改 guest OS 和应用，适合 AI、大数据、HPC 等内存密集型负载。本系列提供基础的 KVM APIC 中断转发支持：拦截 LAPIC 的 ICR/ICR2 MMIO 写，退出到用户态由 GiantVM 运行时路由并重新注入中断，实现跨节点 IPI 协同。CoreMark 测试性能达普通 VM 的 83%–99%。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### io_uring/net: support registered buffer for plain send and recv
- https://lore.kernel.org/all/20260601095853.3670199-1-ming.lei@redhat.com/
- 这组补丁为普通的 send/recv 操作（IORING_OP_SEND / IORING_OP_RECV）增加了对 io_uring 注册缓冲区的支持（IORING_RECVSEND_FIXED_BUF 标志）。此前该标志仅在 SEND_ZC 路径生效。动机：如 ublk 的 NBD 后端等场景，希望通过 TCP 套接字上的普通 send / recv 直接收发注册缓冲区数据，而无需 SEND_ZC 的通知机制。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### nfs: Modernize Direct I/O path
- https://lore.kernel.org/all/20260603053033.3300318-1-praan@google.com
- 该补丁系列对 NFS 直接 I/O 路径进行现代化改造，为后续支持 PCI 点对点 DMA（P2PDMA）做准备。核心改动：1. **引脚感知**：新增 PG_PINNED 标志和 wb_nr_pinned 计数，跟踪物理引脚的所有权，确保 I/O 完成后才解除引脚。2. **API 迁移**：从旧的 iov_iter_get_pages_alloc2() 迁移到现代的 iov_iter_extract_pages() API。3. **folio 支持**：新增提取辅助函数，将同一 folio 的连续页归为单个 nfs_page，使直接 I/O 从基于页转为基于 folio。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### fuse: fix and optimize parallel writes on passthrough mounts
- https://lore.kernel.org/all/20260529031210.7021-1-russ.fellows@gmail.com	
- 该补丁系列修复并优化 FUSE passthrough 挂载上的并行写入。解除并行写阻塞后，将 iocachectr 改为 atomic_t 并添加无锁快速路径，减少 per-inode 自旋锁开销。fio 测试显示 8 线程下 IOPS 从约 63.5 万提升至约 170 万，接近裸 XFS 性能。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### fs,kthread: start all kthreads in nullfs
- 	https://lore.kernel.org/all/20260601-work-kthread-nullfs-v4-0-77ee053060e0@kernel.org
- 该 RFC 补丁系列将所有内核线程（kthread）隔离到独立的 nullfs 内核挂载中，旨在切断内核线程与用户空间 init（PID 1）之间的文件系统状态共享。所有 kthread 锚定在私有的 nullfs 挂载中，无法查找其他路径或被挂载，完全隔离。PID 1 获得独立的 fs_struct，与 kthread 互不影响。提供 scoped_with_init_fs() 让 kthread 在需要时临时借用 init 的 fs_struct。当 PID 1 放弃共享文件系统状态时，主动告警并将其回退到 nullfs，拒绝在过期状态上操作。这使从 kthread 进行路径查找默认失败，强化了安全保证。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: reliable 1GB page allocation
- https://lore.kernel.org/all/20260520150018.2491267-1-riel@surriel.com/
- 该 RFC 补丁系列旨在实现 1GB 大页的可靠分配。它将内存按 PUD 大小划分为"超级页块",将不可移动、可回收等分配集中到已"污染"的块中,保留尽可能多的干净块供可移动分配与碎片整理使用,从而支持 2MB THP 与 1GB 大页的可靠分配。基于 Johannes 的 PCPBuddy 系列以降低性能开销。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2026年 第05期 (Start From 2026/05/01)

#### x86: Try to wrangle PV clocks vs. TSC
- https://lore.kernel.org/all/20260515191942.1892718-1-seanjc@google.com
- 该补丁系列(v3,41个补丁)主要目标:修复SNP/TDX机密虚拟机因使用不可信hypervisor提供的PV时钟而非可信TSC的安全缺陷;次要目标是让KVM guest用TSC作sched_clock并利用CPUID枚举频率;再者统一各hypervisor的PV时钟代码以便维护。改动涉及kvmclock、TSC及各hypervisor客户端代码,KVM部分较有把握,其他仅编译测试。最后两个关于CPUID 0x16获取频率的补丁可选,需Paolo和David W明确ack。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### add kconfirm
- https://lore.kernel.org/all/20260516215354.449807-1-julianbraha@gmail.com
- kconfirm 是检测 Kconfig 误用的工具,可发现死代码、恒定条件、无效范围,并可选检查 select 可见选项及帮助文本中的失效链接。本 RFC v3 拟将其合入内核源码树。在 v7.1-rc3 上默认检查产生 489 条告警,启用 select-visible 检查则增加 1789 条。使用 `make kconfirm` 即可运行,已帮助发现若干 kunit 配置 bug。作者征求反馈:select-visible 检查是否应默认启用,以及实际使用体验。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched/tick: Decouple sched_tick() from HZ
- https://lore.kernel.org/all/20260517040740.444729-1-qyousef@layalina.io/
- 本补丁尝试将 sched_tick() 与 HZ 解耦,避免在定时器频率与调度器更新频率间妥协。此前将默认 HZ 设为 1000 的方案未被合入。随着 HRTICK 默认开启,抢占检查问题减弱,但 HMP 系统上的任务迁移和频率更新仍需更频繁的调度 tick。转换尚未完成,需引入新的 "piffy" 概念并迁移负载均衡逻辑;考虑到 push load balancer 方案,加速完整负载均衡的必要性存疑,但其同样可受益于 ptick。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### vfio/dma-buf: add TPH support for peer-to-peer access
- https://lore.kernel.org/all/20260519201401.1558410-1-zhipingz@meta.com/
- 该补丁系列(v4,3个补丁)为 VFIO dma-buf 导出路径添加 TPH(TLP 处理提示)支持,使 mlx5 等导入驱动在向 VFIO 设备进行点对点 DMA 时可使用导出方的 steering tag。补丁1引入 dma-buf get_tph 回调和新 uAPI;补丁2新增 PCI/TPH 辅助函数暴露已启用的请求类型;补丁3将 mlx5 RDMA 驱动接入。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### killswitch: add per-function short-circuit mitigation primitive
- https://lore.kernel.org/all/20260507070547.2268452-1-sashal@kernel.org
- 该补丁引入 killswitch 机制,作为安全漏洞的临时缓解原语。当漏洞公开后,在补丁内核构建分发并重启前,管理员可通过 `/sys/kernel/security/killswitch/control` 写入函数名和返回值(如 `engage af_alg_sendmsg -1`),使指定函数立即直接返回 -EPERM 而不执行函数体,重启后失效。适用于 AF_ALG、ksmbd、nf_tables、vsock 等少数用户使用的高危子系统,以临时禁用换取整体安全。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: Introduce bpf_netpoll
- https://lore.kernel.org/all/20260511085344.3302-1-mahe.tardy@gmail.com/
- 该补丁集引入 `bpf_netpoll`,一组允许 BPF 程序通过 netpoll 基础设施直接向驱动发送 UDP 包的 kfuncs,绕过常规网络栈。主要用途是让 LSM 等 BPF 程序在用户态 agent 缺失时仍能发出遥测或安全告警(如 Tetragon、Meta BpfJailer 场景),替代 ringbuffer 日志方案。实现沿用 bpf_crypto 的 kfunc 生命周期模式(create/acquire/release + 引用计数 + kptr),并避免网络程序递归问题。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/zswap: Implement per-cgroup proactive writeback
- https://lore.kernel.org/all/20260511105149.75584-1-jiahao.kernel@gmail.com
- 该补丁集为 zswap 增加按 cgroup 主动回写机制。当前 zswap 只在内存压力或池满时被动回写,时机不可控、影响延迟敏感任务。新方案引入 `memory.zswap.proactive_writeback` cgroup v2 接口,用户可指定最小年龄(秒)和可选最大字节数,主动将冷压缩页写回交换设备。同时将全局 shrink 游标改为 per-memcg 的 `zswap_wb_iter`,并新增 `zswpwb_proactive` 计数器统计主动回写次数。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/virtio: skip redundant zeroing of host-zeroed pages
- https://lore.kernel.org/all/cover.1778192416.git.mst@redhat.com
- 该补丁集利用 virtio-balloon free page reporting 后宿主机已对回收页面清零的事实,通过 PG_zeroed(buddy 分配器)和 HPG_zeroed(hugetlb)两个标志在内核中传递"已清零"信息,避免 guest 重新分配时的冗余清零。同时修复 init_on_alloc 在别名缓存架构上的重复清零问题。在 THP 场景下分配 256MB 匿名页,task-clock 与 cache-misses 降低约 70-78%,需新虚拟机特性位 6/7 支持。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### vfio/pci: Base Live Update support for VFIO
- https://lore.kernel.org/all/20260511234802.2280368-1-vipinsh@google.com
- 该补丁集为 VFIO 引入 Live Update 基础支持,通过新增 `VFIO_PCI_LIVEUPDATE` 配置项,允许 VFIO cdev FD 在 kexec 跨内核保留,重启后从 Live Update 子系统取回。当前仅保留 FD,kexec 前会重置设备并禁用 BME 以保证下一内核安全。系列依赖 PCI v4 改动,新增 selftests 与文档,已在 QEMU 和 Intel DSA 实机验证。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### tick/sched: Refactor idle cputime accounting
- https://lore.kernel.org/all/20260508131647.43868-1-frederic@kernel.org/
- 该补丁集重构 idle CPU 时间统计机制。当前在线 CPU(基于 nohz 时间戳,纳秒级但不处理 steal/IRQ 时间)与离线 CPU(基于 jiffies,粒度粗但准确)使用两套互相冲突的统计,导致 CPU 下线后全局 idle 时间倒退。新方案采用混合模式:tick 运行时走原生 vtime,进入 dynticks-idle 后直接累加到内核统计字段,移除私有累加层,统一在线/离线场景,并正确处理 IRQ 与 steal 时间。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；对应改动如「tick/sched: Move dyntick-idle cputime accounting to cput」）

#### sched: Make proxy execution compatible with sched_ext
- https://lore.kernel.org/all/20260506174639.535232-1-arighi@nvidia.com
- 该补丁解除 `CONFIG_SCHED_PROXY_EXEC` 与 `CONFIG_SCHED_CLASS_EXT` 的互斥编译限制,允许同一内核同时支持代理执行(proxy-exec)与 sched_ext。因二者在任务调度视图上存在不一致,加载 sched_ext 调度器时默认关闭 proxy-exec 上下文捐赠,可通过启动参数 `sched_proxy_exec_scx=1` 显式开启,便于发行版统一构建并在运行时灵活选择特性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kho: make boot time huge page allocation work nicely with KHO
- https://lore.kernel.org/all/20260429133928.850721-1-pratyush@kernel.org/
- 该补丁系列旨在解决KHO(Kexec Handover)与启动时大页分配的兼容性问题。当前存在两个问题:一是巨型大页通过memblock分配会计入RSRV_KERN,导致scratch空间计算膨胀甚至分配失败;二是scratch区域不能包含保留内存,若大页从scratch分配将无法被保留。解决方案是引入"扩展scratch区域"概念,内核启动时通过遍历基数树发现空闲内存范围。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add Rust virtio bindings and sample device
- https://lore.kernel.org/all/20260505-rust-virtio-v1-0-9563383909e4@pitsidianak.is
- 该 RFC 补丁系列为 Virtio 驱动 (前端) 添加 Rust 绑定, 并提供一个 virtio-rtc 示例驱动作为概念验证, 该驱动通过 virtqueue 执行能力发现但不注册时钟。作者使用 rust-vmm 的 vhost-device-rtc 后端进行了测试, 并提供了 QEMU 运行示例及输出日志。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: reduce mmap_lock contention and improve page fault performance
- https://lore.kernel.org/all/20260430040427.4672-1-baohua@kernel.org
- 该补丁集旨在减少mmap_lock竞争并提升缺页异常性能。核心思想是:等待I/O完成后的重试无需回退到mmap_lock,可继续复用per-VMA锁;若I/O已完成只是因并发PTE安装导致folio锁获取失败,则保留per-VMA锁且不重试。测试显示:抖音冷启动时mmap_lock读锁等待时间降低96%;在内存受限memcg压力测试中吞吐量提升约2倍,I/O重试浪费大幅减少;匿名页swap-in带宽也有明显改善。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### 1GB superpageblock memory allocation
- https://lore.kernel.org/all/20260430202233.111010-1-riel@surriel.com/
- 该RFC补丁集将内存按PUD大小划分为1GB超级页块,主动将不可移动、可回收及highatomic分配引导至已"污染"的超级页块,从而保留更多仅含可移动分配的超级页块,便于整理为2MB或1GB大页。代码主要由AI编写,作者审阅迭代。在256GB系统测试中,238个超级页块中通常少于20个被不可移动分配占用,可分配50个1GB大页。重点关注超级页块标记追踪、空闲列表、后台碎片整理及分配器适配等补丁。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: Hot page tracking and promotion infrastructure
- https://lore.kernel.org/all/20260504060924.344313-1-bharata@amd.com/
- 该v7补丁集介绍了pghot——热页跟踪与提升子系统。新版本主要新增对AMD IBS内存分析器作为热度数据源的支持。pghot旨在统一来自缺页提示、页表扫描、硬件提示等多种来源的热页检测,将检测与迁移解耦,并通过每个低层节点的kmigrated内核线程集中执行提升逻辑。系统在每个PFN中记录访问频率、时间(默认模式1字节,精确模式4字节,后者还含NUMA节点ID),按阈值标记热页后批量迁移。1TB低层内存开销分别为256MB和1GB。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Virtual Swap Space
- https://lore.kernel.org/all/20260505153854.1612033-1-nphamcs@gmail.com
- 该v6补丁集实现"虚拟交换空间"(vswap),通过引入虚拟交换槽抽象层将交换条目与物理后端解耦。每个交换条目用24字节描述符表示,可绑定到zswap、零页、磁盘或内存等不同后端。主要优势:zswap摆脱对物理swapfile的依赖,可动态调整大小;swapoff无需遍历页表;便于支持多层交换、THP混合换入等新特性。v6重点优化快速后端(zram/PMEM)的CPU和内存开销,通过批处理、per-CPU缓存等手段将性能差距缩小至噪声范围内。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2026年 第04期 (Start From 2026/04/01)

#### KVM: x86/pmu: Add hardware Topdown metrics support
- https://lore.kernel.org/all/20260423174639.56149-1-zide.chen@intel.com
- 该补丁系列在 KVM 中为 guest 添加硬件 Topdown 指标（TMA）支持。当前 guest 只能用通用 GP 计数器收集 Topdown 事件，会触发多路复用并产生偏差。基于新的 mediated vPMU，向 guest 暴露固定计数器 3 和 `IA32_PERF_METRICS` MSR，避免了对 perf 核心的侵入式修改、CPU pinning 和 MSR 陷入模拟开销。在 SPR 上测试，应用本系列后 guest 中 `tma_frontend_bound`、`tma_retiring` 等 metric 事件可正常显示。V2 新增 selftest，并在 host 不支持时不暴露固定计数器 3。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### PCI: liveupdate: PCI core support for Live Update
- https://lore.kernel.org/all/20260423212242.3431136-1-dmatlack@google.com
- 该补丁系列在 PCI 核心层引入 Live Update 支持，使驱动可在基于 kexec 的内核更新中保留 PCI 设备状态而不中断业务，对 VFIO 透传给 VM 的设备至关重要。通过 KHO 机制设置 FLB 处理器保存 `pci_ser` 状态，提供注册"出/入"设备的 API，并自动通过引用计数保留上游桥；继承总线号、ARI、ACS 标志以保持路由与 IOMMU 分组稳定；仅允许保留处于不可变 singleton IOMMU 组的设备；shutdown 路径不再关闭被保留设备的 bus mastering。已在 QEMU 和 Intel EMR 裸机环境配合 VFIO 测试通过。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### nvme: Controller Data Queue (CDQ) support
- https://lore.kernel.org/all/20260424-jag-cdq-lkml-v1-0-d773343a717c@kernel.org/
- 该 RFC 在 NVMe 驱动中实现 Controller Data Queue (CDQ) 支持，提供 ioctl 接口让用户态创建、配置、删除基于 DMA 映射用户内存的 CDQ，并通过 eventfd 通知。本版本将 CDQ 协议逻辑放在内核外，ioctl 仅作测试工具。该工作服务于 NVMe namespace 迁移这一更大目标，但 Live Migration 逻辑归属尚无共识，作者列出两种方案：基于 VFIO 状态机，或绕过 VFIO 在 VM 管理器（如 QEMU）与 NVMe 驱动之间实现。同时强调命名空间数据迁移（可能 TB 级）是值得关注的独立场景。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kdump: reduce vmcore size and capture time via linux,no-dump
- https://lore.kernel.org/all/20260429065831.1510858-1-chenwandun@lixiang.com/
- 该补丁系列通过新增 `linux,no-dump` 设备树预留内存属性来减小 vmcore 体积、加快 kdump 速度。前 4 个补丁修复 OF reserved_mem bug；后续补丁解析该属性并将 `/memreserve/` 固件区域默认标记为 `no_dump`，arm64、riscv、loongarch 在 `prepare_elf_headers()` 中将其从 ELF `PT_LOAD` 段排除。适用于 GPU、DSP、NPU 等大块固件预留区——这些内容对崩溃分析无用。与 `no-map` 兼容，对 `reusable`（CMA）区域忽略，未启用的 DT 行为不变。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Enforce host page-size alignment for shared buffers
- https://lore.kernel.org/all/20260427063108.909019-1-aneesh.kumar@kernel.org/
- 该补丁系列解决私有内存客户机与宿主机共享缓冲区的对齐问题。客户机内核分配共享缓冲区时必须对齐到宿主机页大小，否则当 `guest_memfd` 被 mmap 到用户空间后，应用可能访问超出 4K 共享区的 64K 页内容，进而通过线性映射触发 GPC 故障并导致内核崩溃。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### ext4: use iomap for regular file's buffered I/O path
- https://lore.kernel.org/all/20260422021042.4157510-1-yi.zhang@huaweicloud.com/
- 本系列为 ext4 常规文件实现基于 iomap 的缓冲 I / O 路径，通过 buffered_iomap 挂载选项启用。不支持内联数据、fscrypt、data = journal 等特性时自动回退 buffer_head 路径。始终启用 dioread_nolock 以避免数据暴露。大块写入性能提升 30%-50%，读性能无明显差异。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### virtio: add noirq system sleep PM callbacks for virtio-mmio
- https://lore.kernel.org/all/20260415173833.6319-1-baver.bae@gmail.com/
- 为 virtio-mmio 添加 noirq 阶段系统休眠 PM 回调支持，使 virtio-clock 等基础设备能在常规恢复回调前完成恢复。通过提供 noirq 安全的辅助函数、避免睡眠操作和内存分配，并新增 reset_vqs 传输回调实现 vring 原地重置，解决了 IRQ 禁用环境下的设备初始化问题。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### cgroup/cpuset: Enable runtime update of nohz_full and managed_irq CPUs
- https://lore.kernel.org/all/20260421030351.281436-1-longman@redhat.com
- 本系列扩展 cpuset 隔离分区功能，支持运行时动态更新 nohz_full 和 managed_irq CPU 列表。通过 CPU 热插拔机制，先下线受影响 CPU，修改相关子系统掩码后再上线。需内核启动参数显式启用。已知 stop_machine 机制会对其他隔离分区造成延迟尖峰，待后续解决。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### RCU: Enable callbacks to benefit from expedited grace periods
- https://lore.kernel.org/all/20260417231203.785172-1-puranjay@kernel.org
- RCU 回调此前仅跟踪普通宽限期，即使加速宽限期已完成仍需等待。本系列通过在回调基础设施中同时跟踪普通和加速宽限期序列号，使任一类型完成即可推进回调。包括重构准备、核心推进逻辑修改、通知路径修复及测试支持。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「rcu: Enable RCU callbacks to benefit from expedited grac」）

#### bpf: fsession support
- https://lore.kernel.org/all/20260108022450.88086-1-dongml2@chinatelecom.cn
- BPF 新增 fsession 功能，允许用单个 TRACING 程序同时 hook 函数入口和出口，无需分别定义 FENTRY 和 FEXIT。复用现有 kfunc 接口，支持 session cookie（最多 4 个），目前仅支持 x86_64 架构。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；commit 引用了本系列 Link）

#### userfaultfd: working set tracking for VM guest memory
- https://lore.kernel.org/all/20260414142354.1465950-1-kas@kernel.org
- 该补丁为 userfaultfd 添加虚拟机客户内存工作集追踪能力，使 VMM 能识别冷页并安全驱逐到分层存储。引入匿名内存 minor fault 支持（PROT_NONE 机制）、异步自动解决 minor fault、页面去激活接口及运行时模式切换，支持匿名和 shmem 内存。VMM 可通过去激活→扫描冷页→同步模式驱逐→恢复异步的工作流实现无数据丢失的内存分层管理。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: split the file's i_mmap tree for NUMA
- https://lore.kernel.org/all/20260413062042.804-1-huangsj@hygon.cn/
- 在大规模 NUMA 系统（如 384 CPU / 12 节点）上，execve 时 libc.so 等共享库的 i_mmap 红黑树（可达 6000+ VMA）锁竞争严重。该补丁将文件的 i_mmap 树按 NUMA 节点拆分为多棵兄弟树，降低锁争用。在 UnixBench execl 测试中性能提升约 77%。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### ftrfs: Fault-Tolerant Radiation-Robust Filesystem
- https://lore.kernel.org/all/20260413142357.515792-1-aurelien@hackers.camp/
- FTRFS 是一个面向太空等强辐射环境的容错文件系统，提供三层数据完整性保护：CRC32 校验、Reed-Solomon 前向纠错和 EDAC 错误追踪。已实现超级块挂载、inode 读取、目录操作、文件读写和块分配器，RS 解码器和 fsck 工具待完成。已在 arm64 上通过 Yocto / KVM 环境验证，目前征求社区对磁盘格式和设计方案的反馈。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；commit 引用了本系列 Link）

#### Dynamic Housekeeping Management (DHM) via CPUSets
- https://lore.kernel.org/all/20260413-wujing-dhm-v2-0-06df21caba5d@gmail.com/
- 该补丁引入动态管家管理（DHM），通过 cgroup v2 cpuset 控制器在根 cgroup 暴露 cpuset.housekeeping.cpus 接口，允许运行时动态更新内核全局管家 CPU 掩码，无需重启。支持 RCU NOCB、NOHZ Full、工作队列、定时器、中断亲和、看门狗、调度域隔离、内存管理及内核线程等子系统的动态重配置，便于 Kubernetes 等编排系统灵活管理。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched_ext: Add verifier-time kfunc context filter
- https://lore.kernel.org/all/20260410063046.3556100-1-tj@kernel.org/
- 该补丁将 sched_ext 中 kfunc 的上下文敏感调用限制从运行时检查迁移到 BPF 验证器编译时过滤。过程中先修复了已有的调用点 bug（如 cgroup_move 锁标记错误、set_cpus_allowed_scx 错误传 NULL rq），再逐步转换并通过完整的 kfunc / 调用者判定矩阵验证正确性，最后移除运行时 kf_mask 机制。这提升了安全性并将错误检测提前到编译期。
- 主线状态：✅ 已进入 mainline（约 v7.1-rc2；对应改动如「sched_ext: Add verifier-time kfunc context filter」）

#### VMSCAPE optimization for BHI variant
- https://lore.kernel.org/all/20260414-vmscape-bhb-v10-0-efa924abae5f@linux.intel.com
- 该补丁系列优化了 VMSCAPE 漏洞中 BHI 变体的缓解方案。当前方案在 KVM 退出到用户态时使用 IBPB（开销大），而受 BHI 影响的 CPU（Alder Lake 及更新）只需清除分支历史（BHB-clear）即可。新方案用轻量级 BHB 清除替代 IBPB，在 Emerald Rapids 平台上 iPerf 测试显示网络性能损失从最高 12.5% 降至约 1-3%，显著降低了安全缓解的性能代价。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### fuse: add io-uring buffer rings and zero-copy
- https://lore.kernel.org/all/20260402162840.2989717-1-joannelkoong@gmail.com/
- 该补丁为FUSE over io-uring添加缓冲环和零拷贝能力。缓冲环通过池化payload缓冲区减少内存占用，并支持pin住缓冲区以消除每次请求的pin/unpin开销。零拷贝（仅限特权服务端）让服务端直接操作客户端页面，免除内核与用户空间间的数据拷贝。基准测试显示，pin缓冲区提升约4-10%吞吐，零拷贝提升约10-35%，直接随机读提升最显著。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「fuse: add io-uring buffer pools」）

#### nfs: Enable PCI Peer-to-Peer DMA (P2PDMA) support
- https://lore.kernel.org/all/20260401194501.2269200-1-praan@google.com/
- 该补丁为NFS Direct I/O引入PCIe P2PDMA支持，使数据可在NVMe与网卡间直接传输。主要改动包括：将NFS能力位扩展至64位以容纳新标志；在SunRPC传输层检测RDMA设备的P2PDMA能力；为nfs_page引入PG_PINNED标志实现pin感知的请求生命周期；将Direct I/O路径迁移至iov_iter_extract_pages() API并按需传递P2PDMA标志。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Rust io_uring command abstraction for miscdevice
- https://lore.kernel.org/all/20260408140007.8401-1-sidong.yang@furiosa.ai/
- 该补丁为Linux内核的Rust miscdevice框架引入io_uring命令(`IORING_OP_URING_CMD`)抽象，使Rust驱动能处理io_uring透传命令。包含绑定C头文件、修复PDU零初始化UB问题、核心类型状态抽象、MiscDevice trait扩展uring_cmd回调，以及基于workqueue的异步完成示例。PDU访问采用拷贝方式以避免对齐问题。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched/fair: SMT-aware asymmetric CPU capacity
- https://lore.kernel.org/all/20260403053654.1559142-1-arighi@nvidia.com/
- 该补丁为Linux调度器的非对称CPU容量策略引入SMT感知：当SMT兄弟线程繁忙时，物理核实际算力低于标称值，导致调度器错误选择"高容量"但实际半忙的核。方案优先选择完全空闲的SMT核，并拒绝向繁忙SMT兄弟迁移任务。在NVIDIA Vera Rubin平台上，CPU密集负载性能从约5.5 TFLOPS提升至约9.3 TFLOPS，接近翻倍。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### futex: Address the robust futex unlock race for real
- https://lore.kernel.org/all/20260330114212.927686587@kernel.org/
- 该补丁系列解决了 Linux 内核中 robust futex 解锁的竞态条件问题：解锁与清除list_op_pending指针非原子操作，若任务在此窗口被强制退出，可能导致 UAF（释放后使用）甚至内存损坏。方案通过内核辅助（合并解锁与指针清除操作、VDSO 辅助函数及内核修复机制），确保指针在退出清理前被清除。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Enable lock context analysis
- https://lore.kernel.org/all/20260325214518.2854494-1-bvanassche@acm.org/
- 该补丁系列为 Linux 块层核心及所有块驱动启用基于 Clang 的锁上下文分析。此前内核已合并从 sparse 转向 Clang 进行锁上下文注解验证的支持，Clang 能力更强（如支持__cond_acquires()和__guarded_by()）。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；对应改动如「block: Enable lock context analysis」）

#### RDMA/rxe: Add dma-buf support for Soft-RoCE
- https://lore.kernel.org/all/20260326052739.3778-1-yanjun.zhu@linux.dev/
- 该补丁为 Soft-RoCE（RXE）驱动添加 dma-buf 支持。此前 RXE 仅支持基于系统内存的用户空间内存区域，现通过 dma-buf 可与 GPU 等设备进行零拷贝数据传输，实现软件定义 RDMA 环境下的 P2P 工作流。补丁已通过 rdma-core 测试验证。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### iommu/amd: Introduce AMD Hardware-accelerated Virtualized IOMMU (vIOMMU) Support
- https://lore.kernel.org/all/20260330084206.9251-1-suravee.suthikulpanit@amd.com/
- AMD 提出 vIOMMU 补丁系列，通过硬件加速虚拟化 IOMMU，将 Guest 命令缓冲区、事件日志和 PPR 日志的操作直接由 IOMMU 硬件处理，无需 HV 拦截模拟，降低 CPU 开销和延迟。该系列共 22 个补丁，基于 IOMMUFD 框架实现，涵盖 MMIO 映射、私有地址空间、转换 DTE 及硬件队列等支持，后续还将添加扩展中断重映射和 Guest 事件注入功能。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### block: Introduce a BPF-based I/O scheduler
- https://lore.kernel.org/all/20260327114741.91500-1-pilgrimtao@gmail.com/
- 该 RFC 提出一种基于 BPF 的新型 I / O 调度器 UFQ，将调度策略从内核移至用户空间，通过在内核实现简单电梯调度器并暴露 BPF 钩子，由用户态 BPF 程序定义调度逻辑，大幅提升灵活性。该补丁依赖尚未合入主线的 BPF 新功能，目前仍处于实验阶段，仅完成基础测试，作者征求社区对方向和实现方案的反馈意见。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### ublk: add shared memory zero-copy support
- https://lore.kernel.org/all/20260328134909.3207377-1-ming.lei@redhat.com/
- 该补丁为 ublk 添加基于共享内存的零拷贝支持。ublk 服务端与客户端通过 MAP_SHARED 映射共享内存区域（如 memfd 或 hugetlbfs），服务端向内核注册该区域，内核钉住页面并构建 PFN maple tree。I / O 到达时，驱动匹配 bio 页面与已注册缓冲区，命中则直接使用数据，避免拷贝。系列共 8 个补丁，含内核实现和自测支持。
- 主线状态：✅ 已进入 mainline（约 v7.1-rc1；对应改动如「selftests/ublk: add shared memory zero-copy support in k」）

#### mm/swap, memcg: Introduce swap tiers for cgroup based swap control
- https://lore.kernel.org/all/20260325175453.2523280-1-youngjun.park@lge.com/
- 该补丁系列引入 Swap Tiers 机制，将 swap 设备按性能分组（如 NVMe、HDD、网络），并允许 per-memcg 选择可用的 swap 层级，子 cgroup 只能使用父级允许的子集。典型场景包括延迟敏感应用使用快速 swap、后台任务使用慢速 swap。实测冷启动性能提升 68%-80%，无配置时性能回归低于 1%。接口集成于 memcg，保持层级继承语义一致性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认


## 2026年 第03期 (Start From 2026/03/01)

#### Use killable vma write locking in most places
- https://lore.kernel.org/all/20260322054309.898214-1-surenb@google.com/
- 该补丁将多数vma_start_write替换为可中断的vma_start_write_killable，提高对kill信号响应；部分关键路径因一致性或复杂性未改。系列含清理、主体修改及错误处理完善。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### dax/kmem: atomic whole-device hotplug via sysfs
- https://lore.kernel.org/all/20260321150404.3288786-1-gourry@gourry.net/
- 该补丁为dax/kmem引入sysfs“hotplug”属性，实现整设备内存原子热插拔，避免逐块操作的竞态问题，并支持在线策略控制。前半部分重构mm/dax基础，后半实现功能，兼容旧行为。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### steal tasks to improve CPU utilization
- https://lore.kernel.org/all/20260320055920.2518389-1-chenjinghuang2@huawei.com
- 该补丁在CPU空闲且idle_balance失败时，从同LLC中过载CPU窃取可迁移任务，并用稀疏位图高效定位目标，提升利用率与性能。实验显示CPU忙碌度最高达95%，性能提升最高17.8%，开销较小。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### fs,x86/resctrl: Add kernel-mode (e.g., PLZA) support to the resctrl subsystem
- https://lore.kernel.org/all/cover.1773347820.git.babu.moger@amd.com/
- 该补丁为resctrl引入AMD PLZA支持，使内核态可使用独立CLOSID/RMID，避免受用户态资源限制影响。新增kernel_mode与kernel_mode_assignment接口，实现模式切换与资源组分配，提升内核性能并支持通用扩展。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### io_uring: add IPC channel infrastructure
- https://lore.kernel.org/all/20260313130739.23265-1-git@danielhodges.dev/
- 该RFC为io_uring引入IPC通道，基于共享内存环形缓冲与无锁机制，实现单播、广播和组播通信，并支持多进程订阅与权限控制。相比传统pipe/socket，在多接收者场景性能显著提升，尤其广播效率更高。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kallsyms: embed source file:line info in kernel stack traces
- https://lore.kernel.org/all/20260312030649.674699-1-sashal@kernel.org/
- 该补丁集新增CONFIG_KALLSYMS_LINEINFO，在内核中嵌入源码文件与行号信息，使堆栈跟踪可直接定位代码位置，无需外部调试符号或工具。支持模块、压缩存储并保证NMI安全，显著提升崩溃调试效率，代价为约6MB内存开销。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### ext4: fast commit: snapshot inode state for FC log
- https://lore.kernel.org/all/20260317084624.457185-1-me@linux.beauty
- 该RFC提出ext4 fast commit改进：通过在提交时快照inode及映射范围，避免在持锁路径调用ext4_map_blocks，从而消除ABBA死锁风险。方案结合extent cache并在异常时回退全量提交，同时限制快照规模，保证性能与正确性。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；对应改动如「ext4: fast commit: snapshot inode state before writing l」）

#### Introduce meminspect
- https://lore.kernel.org/linux-mm/20260311-minidump-v2-v2-0-f91cedc6f99e@oss.qualcomm.com/
- 该补丁集引入meminspect机制，用于在内核中标记内存区域以便转储与分析，适用于传统pstore、kdump不可用场景。其可生成精简core供crash/gdb分析，并提供API供驱动访问，已集成Qualcomm minidump与Android debug kinfo后端，提升调试能力与适用性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### dma-buf: heaps: system: add an option to allocate explicitly decrypted memory
- https://lore.kernel.org/all/20260305123641.164164-1-jiri@resnulli.us/
- 该补丁为 dma-buf system heap 增加显式分配解密（共享）内存的选项，用于 SEV/TDX 等机密计算虚拟机中不支持加密内存 DMA 的设备。用户空间可 mmap 并通过 dma-buf 在 RDMA、DRM 等设备间共享，同时改进 DMA API 支持多设备映射。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched_ext: Document task ownership state machine
- https://lore.kernel.org/all/20260304153343.340285-1-arighi@nvidia.com/
- 该补丁为 sched_ext 中的任务所有权状态机补充文档，系统说明各状态转换及其同步规则，以解决代码中涉及跨 CPU 同步和内存序导致难以理解的问题，从而提升代码可读性与可维护性。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc4；对应改动如「sched_ext: Document task ownership state machine」）

#### Documentation: real-time: Add kernel configuration guide
- https://lore.kernel.org/all/20260305205023.361530-2-darwi@linutronix.de/
- 该补丁新增 实时内核配置指南文档，列出建议启用或禁用的 Kconfig 选项，并提供目录及相关内核指南（如 cpuidle、cpufreq、电源管理、no_hz）的链接，同时提醒实时系统配置需根据具体场景调整，不存在通用方案。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「Documentation: real-time: Add kernel configuration guide」）

#### Two-pass MMU interval notifiers
- https://lore.kernel.org/all/20260305093909.43623-1-thomas.hellstrom@linux.intel.com/
- 该补丁系列为 MMU interval notifier 引入“两阶段通知”机制：第一阶段向所有 GPU 发起抢占或 TLB 刷新请求，第二阶段等待完成，以提升多 GPU 场景的扩展性；并提供 xeKMD userptr 失效与 TLB 刷新的 POC 实现。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm, kvm: allow uffd support in guest_memfd
- https://lore.kernel.org/all/20260306171815.3160826-1-rppt@kernel.org/
- 该补丁系列为 guest_memfd 引入 userfaultfd 支持。通过重构匿名和 shmem 内存的 UFFD 处理并使用 vm_uffd_ops，实现页分配与缓存管理；新增 VM_FAULT_UFFD_* 标志通知用户态处理缺页，目前暂未支持 hugetlb。
- 主线状态：✅ 已进入 mainline（约 v7.1-rc1；commit 引用了本系列 Link）

#### KVM: VMX APIC timer virtualization support
- https://lore.kernel.org/all/cover.1772732517.git.isaku.yamahata@intel.com/
- 该补丁系列为 KVM VMX 引入 APIC 定时器虚拟化支持，使虚拟机可直接使用 TSC deadline 定时器并减少 VM Exit，从而降低定时器延迟；同时支持嵌套虚拟化（nVMX）、自测与文档更新，在部分场景下显著提升性能。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add RMPOPT support
- https://lore.kernel.org/all/cover.1772486459.git.ashish.kalra@amd.com/
- 该补丁为 SEV-SNP 引入RMPOPT优化支持，通过RMPOPT指令在确认1GB内存区域仅由Hypervisor拥有时跳过RMP写检查，以降低性能开销。补丁同时管理RMPOPT表、支持最高2TB内存优化，并新增guest_memfd清理接口及debugfs状态查询。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### iommufd: Enable noiommu mode for cdev
- https://lore.kernel.org/all/20260227175247.26103-1-jacob.pan@linux.microsoft.com/
- 该补丁为 IOMMUFD 的cdev设备增加No-IOMMU模式支持，使无硬件IOMMU平台的用户态驱动也可使用IOAS与HWPT对象。此举改进页固定与DMA物理地址获取机制，使No-IOMMU设备更完整地融入IOMMU子系统，并支持热重置与热更新场景。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### nvme: switch to libmultipath
- https://lore.kernel.org/all/20260225154007.1033735-1-john.g.garry@oracle.com/
- 该补丁将 NVMe host driver 的多路径实现切换为使用libmultipath库，原nvme_ns_head与nvme_ns相关逻辑由mpath_head、mpath_disk等结构替代。补丁先引入libmultipath代码再完成整体切换，以保持构建与功能稳定。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2026年 第02期 (Start From 2026/02/01)

#### 6.6 to be supported for 4 years
- bump the longterm EOL dates to a be a bit longer than previously documented 
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认
#### kernel/website.git 
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认
#### Kernel.org website source
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: tracing_multi link
- https://lore.kernel.org/all/20260220100649.628307-1-jolsa@kernel.org
- 该补丁新增tracing_multi link，支持一次将BPF tracing程序快速附加到多个函数，重构trampoline与link结构，加入session与cookies支持，并补充测试与优化。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；commit 引用了本系列 Link）

#### pid_namespace: make init creation more flexible
- https://lore.kernel.org/all/20260220164559.2465466-1-ptikhomirov@virtuozzo.com/
- 该补丁允许在创建pid命名空间init前先加入该命名空间，使不同进程分步创建namespace与init，提升clone3(set_tid)通用性，并利于CRIU处理嵌套容器。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add virtualization support for EGM
- https://lore.kernel.org/all/20260223155514.152435-1-ankita@nvidia.com/
- 该RFC为Grace Hopper/Blackwell的EGM扩展GPU内存引入虚拟化支持，将主机内存划分为Hypervisor区与对宿主不可见的EGM区，供VM高带宽访问。新增nvgrace-egm辅助驱动，通过字符设备映射EGM至QEMU，处理拓扑、清零与poison页，并配合ACPI与IOMMU实现管理。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Private Memory Nodes (w/ Compressed RAM)
- https://lore.kernel.org/all/20260222084842.1824063-1-gourry@gourry.net/
- 该RFC提出N_MEMORY_PRIVATE私有NUMA节点状态，使内存由buddy管理但默认隔离于常规分配，通过__GFP_PRIVATE与node_private_ops按需接入迁移、mempolicy、回收等mm能力。基于此实现Compressed RAM（cram），以只读映射与回迁机制避免压缩容量失控，支持CXL等设备内存，更简洁替代部分ZONE_DEVICE场景。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### guest_memfd: Track amount of memory allocated on inode
- https://lore.kernel.org/all/cover.1771826352.git.ackerleytng@google.com/
- 该RFC为guest_memfd在inode上跟踪已分配内存，更新i_blocks与i_bytes，使fstat()能正确返回st_blocks。通过在分配与截断时维护字段，并实现自定义truncate函数以便未来扩展；同时改进folio分配流程，为统计更新与问题排查打基础。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### x86/msr: Inline rdmsr/wrmsr instructions
- https://lore.kernel.org/all/20260218082133.400602-1-jgross@suse.com/
- 该补丁在CONFIG_PARAVIRT_XXL下改为内联RDMSR/WRMSR指令，减少裸机下paravirt调用开销，并重构MSR访问与补丁机制，兼容Xen PV与裸机运行。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### support file system generated / verified integrity information v3
- https://lore.kernel.org/all/20260218061238.3317841-1-hch@lst.de/
- 该补丁将T10 PI完整性生成与校验上移至文件系统，实现更大保护范围与更高读性能，重构块层PI代码并在iomap/XFS中接入，为io_uring透传及fsverity等功能铺路。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Open HugeTLB allocation routine for more generic use
- https://lore.kernel.org/all/cover.1770854662.git.ackerleytng@google.com/
- 该RFC重构HugeTLB分配逻辑，提供不依赖VMA的hugetlb_alloc_folio()以通用分配大页，解耦预留与计费机制，便于guest_memfd等场景并简化原有实现。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Improve proc RSS accuracy
- https://lore.kernel.org/all/20260217161006.1105611-1-mathieu.desnoyers@efficios.com/
- 该补丁引入分层树计数器（hpcc）提升/proc中RSS统计精度，将误差从约1GB降至约80MB，并提供误差上限与KUnit测试，优化原有近似实现。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm, swap: swap table phase III: remove swap_map
- https://lore.kernel.org/all/20260218-swap-table-p3-v3-0-f4e34be021a7@tencent.com/
- 该补丁移除静态swap_map，直接用swap table计数，节省约30%交换元数据内存（1TB省256MB），性能略升；后续将合并cgroup数组，实现更动态与低锁争用设计。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add the the capability to load HW RX checsum in eBPF programs
- https://lore.kernel.org/all/20260217-bpf-xdp-meta-rxcksum-v3-0-30024c50ba71@kernel.org/
- 该补丁为eBPF新增bpf_xdp_metadata_rx_checksum()接口，使XDP程序读取网卡硬件RX校验结果，支持veth和ice驱动，可结合哈希信息用于丢弃校验失败等异常流量。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### eBPF isolation with pkeys
- https://lore.kernel.org/all/aY3+Raf8eZqipCd6@e129823.arm.com/
- 该议题提议利用ARMv8.9 POE的pkeys机制隔离eBPF，将其内存与内核默认内存分离，仅允许经helper/KFUNC访问，防范verifier漏洞，并设计pkey感知的内存分配API。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rust: add a ring buffer implementation
- https://lore.kernel.org/all/20260215-ringbuffer-v1-1-9b359758a1b6@kernel.org/
- 该补丁为Rust新增固定容量FIFO环形缓冲区，实现基于循环数组的O(1)入队出队，并提供基础、回绕及边界情况测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Machine Learning (ML) library in Linux kernel
- https://lore.kernel.org/all/20260206191136.2609767-1-slava@dubeyko.com/
- 该补丁提议在内核引入ML库，定义内核与用户态模型交互API，用于数据收集、训练、推理与反馈，辅助子系统配置优化与逻辑生成，并设计多种协作运行模式。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Implementation of Dynamic Housekeeping & Enhanced Isolation (DHEI)
- https://lore.kernel.org/all/20260206-feature-dynamic_isolcpus_dhei-v1-0-00a711eb0c74@gmail.com/
- 该RFC提出DHEI机制，通过sysfs实现运行时动态调整housekeeping与CPU隔离，协调IRQ、RCU、kthread等子系统，支持动态NOHZ_FULL与SMT感知，突破仅能启动时配置的限制。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### io_uring: add kernel-managed buffer rings
- https://lore.kernel.org/all/20260210002852.1394504-1-joannelkoong@gmail.com/
- 该补丁为io_uring引入内核管理的buffer ring，由内核分配和维护缓冲区，替代应用自行管理，便于如fuse over io_uring等场景共享与统一管理缓冲区。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rust: pci: add abstractions for SR-IOV capability
- https://lore.kernel.org/all/20260205-rust-pci-sriov-v2-0-ef9400c7767b@redhat.com/
- 该补丁为Rust PCI驱动加入SR-IOV抽象，封装启停与PF/VF查询，扩展Driver回调处理sriov_numvfs，保证VF与PF绑定关系，并在解绑时自动禁用SR-IOV，附示例驱动。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: Introduce resizable hash map
- https://lore.kernel.org/all/20260205-rhash-v1-0-30dd6d63c462@meta.com
- 该补丁引入可扩展哈希表BPF_MAP_TYPE_RHASH，基于rhashtable支持自动扩缩容，提升内存与性能适应性，支持标准与批量操作、迭代器及并发锁，并含完整测试。
- 主线状态：✅ 已进入 mainline（commit 引用了本系列 Link）

#### Allow preemption during IPI completion waiting to improve real-time performance
- https://lore.kernel.org/all/20260203112401.3889029-1-zhouchuyi@bytedance.com
- 该补丁允许IPI等待期间可抢占，缩短TLB flush等路径关抢占时间，显著降低调度延迟，P99降约90%，提升实时性能。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### AI review prompt updates
- https://lore.kernel.org/all/b187e0c1-1df8-4529-bfe4-0a1d65221adc@meta.com/
- 作者更新AI代码评审提示，将大diff拆为多任务逐块审查，配合脚本预提取结构以降token、提效率并增缺陷发现；新增lore、Fixes、syzkaller校验与总报告任务，征求反馈。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### ptp: vmclock: Add VM generation counter and ACPI notification
- https://lore.kernel.org/all/20260130173704.12575-1-itazur@amazon.com/
- 该补丁为VMClock增VM代际计数与ACPI通知，区分快照恢复与迁移；快照时递增代际计数，通知用户态处理UUID、网络、熵池等重建。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Documentation: Project continuity
- https://lore.kernel.org/all/20260124012256.1856709-1-dan.j.williams@intel.com/
- 该补丁新增“项目连续性”文档，制定当主线仓库维护者（如Linus）无法继续履职时的应急接替流程：由维护者峰会组织者或LF TAB主席牵头，72小时内召集峰会成员与TAB开会，必要时扩展参与者，讨论主仓库管理接替方案，并在两周内向社区公布后续步骤，由Linux基金会支持落实。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「Documentation: Project continuity」）

#### kho: history: track previous kernel version and kexec boot count
- https://lore.kernel.org/all/20260126-kho-v5-0-7cd0f69ab204@debian.org
- 该补丁集通过KHO在kexec启动间传递“上一内核版本号”和“自冷启动以来的kexec次数”，并在新内核早期启动时打印。用于排查仅在特定内核版本切换或多次kexec后才出现的隐蔽问题，便于大规模环境中关联崩溃与前序内核，提升调试与问题定位能力。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### net: fec: improve XDP copy mode and add AF_XDP zero-copy support
- https://lore.kernel.org/all/20260123022143.4121797-1-wei.fang@nxp.com/
- 该补丁为NXP FEC网卡优化XDP copy模式并新增AF_XDP零拷贝支持：拆分RX XDP处理路径、TX批量发送减少MMIO、改进TX回收逻辑，整体提升收发性能；实测xdp-bench与xdpsock显示copy模式吞吐提升，zero-copy模式性能显著高于copy模式。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；对应改动如「net: fec: add AF_XDP zero-copy support」）

## 2026年 第01期 (Start From 2026/01/01)

#### DAXFS: A zero-copy, dmabuf-friendly filesystem for shared memory
- https://lore.kernel.org/all/CAGHCLaREA4xzP7CkJrpqu4C=PKw_3GppOUPWZKn0Fxom_3Z9Qw@mail.gmail.com/
- DAXFS是面向共享物理内存的只读DAX文件系统，支持从连续内存或dma-buf零拷贝读取，绕过页缓存和块I/O，实现真实物理页共享。适用于多内核/容器共享镜像、CXL内存池、加速器数据访问等场景，结构简单，含内核模块与镜像制作工具。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### x86,fs/resctrl: Support for Global Bandwidth Enforcement and Priviledge Level Zero Association
- https://lore.kernel.org/all/cover.1769029977.git.babu.moger@amd.com/
- 该 RFC 补丁集为 x86 的 fs/resctrl 子系统新增 AMD 全局带宽管控能力：GLBE 与 GLSBE，用于跨多个 QoS Domain 的 L3 外部及慢内存带宽统一限速，并引入 PLZA，使 CPL0 内核态执行可自动绑定到指定 COS/RMID。补丁新增 GMB/GSMBA 资源、最大带宽与 PLZA 控制接口，并更新文档。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched/fair: Improve nohz fields for large systems
- https://lore.kernel.org/all/20260115073524.376643-1-sshegde@linux.ibm.com/
- 该补丁集针对大型系统中 sched/fair 的 nohz.nr_cpus 缓存行争用问题。由于频繁的原子增减与读取，导致严重 cacheline 抖动。前两补丁为小修正，第三个核心补丁移除 nr_cpus，改用同步维护的 cpumask 表示 CPU 数量，功能等价且显著降低争用；idle_cpus_mask 的争用仍未解决。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Interrupt storm detection
- https://lore.kernel.org/all/20260115074909.245852-1-crajank@nvidia.com/
- 该补丁集引入通用的中断风暴（Interrupt Storm）检测机制，并在 mlxreg-hotplug 驱动中启用。按 Thomas Gleixner 建议实现通用框架，驱动侧通过回调在共享 IRQ 上按设备统计中断次数以识别风暴；同时修订逻辑并修复前版评审意见，提升中断异常检测与稳定性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Global Software Interrupt Moderation (GSIM)
- https://lore.kernel.org/all/20260115155942.482137-1-lrizzo@google.com/
- 该补丁集提出 GSIM（全局软件中断调节），通过高效统计全局及每 CPU 的中断速率与 hardirq 占比，动态调整各中断源的调节延迟，解决 MSI-X 中断过高导致的大型平台性能骤降问题。GSIM 无需硬件支持，在高负载时限流、低负载几乎无延迟，显著提升网络与存储吞吐且不影响低负载延迟。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### virtio-gpu: Add userptr support for compute workloads
- https://lore.kernel.org/all/20260115075851.173318-1-honglei1.huang@amd.com/
- 该补丁集为 virtio-gpu 增加 userptr 支持，使宿主机可零拷贝访问来宾用户态内存，面向 GPU 计算负载并支持 ROCm 原生上下文。通过页长期固定与 SG 表实现高效计算，提供读写 userptr、能力发现与 DRM UAPI 扩展。在多平台测试中计算性能可达裸机的约 70%～92%。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Allow ATS to be always on for certain ATS-capable devices
- https://lore.kernel.org/all/cover.1768624180.git.nicolinc@nvidia.com/
- 该 RFC 补丁提议允许对部分 ATS 能力设备始终启用 PCI ATS，即使其 RID 处于 IOMMU bypass 且无 PASID/SVA 场景。针对支持非 PASID ATS 的设备（如 CXL.cache、部分 NVIDIA GPU），新增能力检测与设备 ID 扫描辅助函数，并在 ARM SMMUv3 中引入 per-device 的 ats_always_on 标志以适配驱动行为。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；对应改动如「PCI: Allow ATS to be always on for pre-CXL devices」）

#### fuse/io-uring: add kernel-managed buffer rings and zero-copy
- https://lore.kernel.org/all/20260116233044.1532965-1-joannelkoong@gmail.com/
- 该补丁集为基于 io-uring 的 FUSE 引入内核管理的缓冲区环（kmbuf）和零拷贝能力，由内核统一分配与回收缓冲，降低内存开销并简化用户态。零拷贝在大块 I/O 下显著提升读性能（约 20%～25%），写入提升有限，整体增强 FUSE 吞吐与可扩展性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Migrate on fault for device pages
- https://lore.kernel.org/all/20260114091923.3950465-1-mpenttil@redhat.com/
- 该补丁集针对设备页缺页与迁移流程低效问题，提出在一次页表遍历中同时完成缺页处理和迁移。通过新增 HMM_PFN_REQ_MIGRATE 与 MIGRATE_VMA_FAULT 标志，将 fault 与 migrate 结合，避免多次页表遍历带来的性能开销，并已在 x86-64 环境通过测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: Reduce latency of OOM killer task selection
- https://lore.kernel.org/all/20260113200428.30614-1-mathieu.desnoyers@efficios.com/
- 该补丁集通过引入层次化树计数近似（hpcc）和两遍算法，优化 OOM killer 任务选择流程，显著降低选择延迟。在大量进程场景下性能提升明显，将原本数十毫秒降至个位数毫秒，定位为 OOM killer 的延迟优化改进。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### BPF-based NUMA balancing
- https://lore.kernel.org/all/20260113121238.11300-1-laoar.shao@gmail.com/
- 该 RFC 补丁提出基于 BPF 的 NUMA 负载均衡方案，在全局禁用 NUMA balancing 的前提下，按工作负载精细化启用与调优。通过新增 BPF struct-ops 钩子按 cgroup 控制迁移策略，提升跨 NUMA 性能并降低系统开销，目前仍属初步方案。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: Fix OOM killer inaccuracy on large many-core systems
- https://lore.kernel.org/all/20260111150249.1222944-1-mathieu.desnoyers@efficios.com/
- 该补丁集通过引入层次化的每 CPU 计数器，解决了大规模多核系统中 OOM killer 因 RSS 跟踪不准确导致的错误杀死进程问题。通过优化每 CPU 内存计数器，减少调度引起的误差，并提高 OOM 决策的准确性。此次改进有助于在多核环境下提升监控精度，并确保 OOM 操作更精确。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；对应改动如「mm: fix OOM killer inaccuracy on large many-core systems」）

#### fs: add immutable rootfs
- https://lore.kernel.org/all/20260112-work-immutable-rootfs-v2-0-88dd1c34a204@kernel.org/
- 该补丁集引入了不可变的根文件系统“nullfs”，用于解决 pivot_root() 在真实根文件系统上无法卸载的问题。通过在内核中挂载一个空的“nullfs”根文件系统，简化了初始化过程，避免了手动移除 initramfs 内容，提升了根文件系统的挂载和卸载操作的灵活性。此改进还支持在无特权的命名空间中创建空的挂载命名空间。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### CXL: Introduce memory controller abstraction and sysram controller
- https://lore.kernel.org/all/20260112163514.2551809-1-gourry@gourry.net/
- 该补丁集为 CXL 引入了内存控制器抽象，并增加了“sysram”控制器，简化了内存热插拔操作，避免了通过 DAX 子系统进行繁琐的区域管理。补丁包括支持多种内存控制器模式、直接热插拔内存、改进内存控制器逻辑、以及为 sysram 提供更灵活的默认状态和配置选项。此改进为未来支持不同内存控制器逻辑（如私有 NUMA 节点）做准备。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Link the relocatable x86 kernel as PIE
- https://lore.kernel.org/all/20260108092526.28586-21-ardb@kernel.org/
- 该补丁集旨在将 x86_64 内核链接为 PIE（位置独立可执行文件），以支持进一步的安全强化措施，如 fg-kaslr 和架构间引导协议的统一。虽然 PIE 编译曾因增加代码大小和可能的性能问题被反对，但此系列通过不使用 GOT 插槽的方式实现了 PIE 编译，代码增量仅为 0.2% 到 0.5%，且未发现性能回退。此改动为 fg-kaslr 提供了基础，增强内核安全性，特别是在执行不可修改代码映射的环境中。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add READ_ONCE and WRITE_ONCE to Rust
- https://lore.kernel.org/all/20251231-rwonce-v1-0-702a10b85278@google.com
- 该补丁系列为内核 Rust 代码引入 READ_ONCE / WRITE_ONCE，用于替换不恰当的 volatile 访问。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: Extend bpf syscall with common attributes support
- https://lore.kernel.org/all/20260106165907.53631-1-leon.hwang@linux.dev/
- 该补丁系列在先前讨论基础上，扩展了 BPF 系统调用，支持通用属性，提供统一的机制来传递共享的元数据。新增的属性包括：log_buf（日志缓冲区）、log_size（缓冲区大小）、log_level（日志级别）、log_true_size（内核报告的日志大小）。此扩展将改善错误报告功能，如在创建 map 失败时提供有意义的错误信息，提升调试性和用户体验。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；对应改动如「bpf: Extend BPF syscall with common attributes support」）

#### Improve khugepaged scan logic
- https://lore.kernel.org/all/20251229055151.54887-1-yanglincheng@kylinos.cn/
- 该补丁系列优化了 khugepaged 扫描逻辑，减少了 CPU 消耗，并优先扫描频繁访问内存的任务。改进包括跳过无法合并成大页的内存、跳过用户标记为冷或即将释放的内存区域（通过 MADV_COLD/MADV_FREE）。性能测试显示，应用补丁后，任务的访问时间和缓存缺失减少，吞吐量提升，尤其在内存访问频繁的场景下表现更佳。补丁基于 Linux v6.19-rc2 开发。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### virtio_net: add page_pool support
- https://lore.kernel.org/all/20260106221924.123856-1-vishs@meta.com/
- 该补丁系列为 virtio_net 驱动添加了 page_pool 支持，用于在 RX 缓冲区分配中回收页面，避免通过页面分配器重新分配内存，适用于可合并和小缓冲区模式。补丁经过自测试和边缘案例脚本验证，包括设备解绑/绑定、快速接口开关、流量关闭时的处理、ethtool 压力测试等，确保数据完整性和稳定性。
- 主线状态：✅ 已进入 mainline（约 v7.1-rc1；对应改动如「virtio_net: add page_pool support for buffer allocation」）

## 2025年 第12期 (Start From 2025/12/01)

#### KVM: VMX: Introduce Intel Mode-Based Execute Control (MBEC)
- https://lore.kernel.org/all/20251223054806.1611168-1-jon@nutanix.com
- 该补丁在 KVM 中引入 **Intel MBEC** 支持，使嵌套 VMX 的 L2 客户机可使用硬件模式控制执行权限，大幅减少 Windows HVCI 下的 VMexits（约 24 倍），显著提升虚拟化性能，同时保持非 MBEC 情况下的低开销。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: x86: Enable APX for guests
- http://lore.kernel.org/all/20251221040742.29749-1-chang.seok.bae@intel.com
- 该补丁为 KVM x86 启用 **APX 扩展寄存器支持**，包括 GPR 访问器重构、VMX EGPR 索引支持、REX2 指令前缀仿真优化，以及 APX 功能暴露与自测，实现更简洁高效的寄存器扩展管理。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### erofs: Introduce page cache sharing feature
- https://lore.kernel.org/all/20251223015618.485626-1-lihongbo22@huawei.com/
- 该补丁在 EROFS 文件系统中引入 共享页缓存 功能，可在容器场景下对相同内容文件复用缓存，显著降低内存使用，实验显示文件读取内存降低16%~49%，容器运行内存降低4%~47%。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Enable compound page for p2pdma memory
- https://lore.kernel.org/all/20251220040446.274991-1-houtao@huaweicloud.com/
- 该系列补丁为 **p2pdma 内存**启用复合页支持，可显著降低 struct page 开销并提升大页（2MB/1GB）用户映射性能，实现 NVMe SSD 到 NPU 的高效直连传输，用户态 mmap 延迟由 0.8s 降至 0.04ms。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### nova-core: Memory management initial patches
- https://lore.kernel.org/all/20251219203805.1246586-1-joelagnelf@nvidia.com
- 该 RFC v5 系列为 **nova-core GPU 驱动**引入初始内存管理基础设施，整合 clist、GPU buddy 分配器及其 Rust 绑定，并加入 PRAMIN 窗口以在页表初始化前直访 VRAM，配套文档与自测。该系列基于 drm-rust-next，为后续页表与映射支持奠定基础。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Implement initial driver for virtio-RDMA device(kernel)
- https://lore.kernel.org/all/20251218091050.55047-1-15927021679@163.com/
- 该邮件介绍了 **virtio-RDMA 内核驱动的初始实现**，通过 vhost-user 在无物理 RDMA 网卡的情况下模拟 Soft-RoCE。文中给出基于 DPDK、QEMU 和 vRDMA 模块的完整测试环境与流程，验证了虚拟 RDMA 设备的发现与基本功能（CM、UC/UD QP 等）可用，功能测试全部通过，并列出后续待完善的特性与性能优化方向。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### LLMinus: LLM-Assisted Merge Conflict Resolution
- https://lore.kernel.org/all/20251219181629.1123823-1-sashal@kernel.org/
- 该 RFC 介绍 **LLMinus**：一个利用 LLM 辅助内核维护者解决合并冲突的工具。它从内核历史中学习人工冲突解决模式，构建语义向量库，在出现冲突时检索相似案例并引导 LLM分析。LLMinus 可直接对接 lore.kernel.org，辅助 pull 与冲突决策，目标是减轻维护者合并负担并提升一致性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rust: conclude the Rust experiment
- https://lore.kernel.org/all/20251213000042.23072-1-ojeda@kernel.org/
- 该补丁宣布 **Linux 内核中的 Rust 试验正式结束**。Rust 自 6.1 合入后已在生产环境、发行版和 Android 中广泛使用，维护者峰会认定其可行性已验证。尽管仍有配置和工具链问题待完善，但结论是*Rust 将长期成为内核一部分**，并希望推动更多投入与采用。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「rust: conclude the Rust experiment」）

#### ext4: defer unwritten splitting until I/O completion
- https://lore.kernel.org/all/20251213022008.1766912-1-yi.zhang@huaweicloud.com/
- 该补丁系列将 **ext4 未写入 extent 的拆分** 从 I/O 提交阶段延后到 **I/O 完成时**。通过依赖 NOFAIL 与 MAY_ZEROOUT 机制，确认不会增加 ENOSPC 下的写失败或数据丢失风险。延后拆分可合并写回、减少不必要拆分和日志开销，简化 I/O 路径，并在并发 DIO 写入预分配文件时带来约 **25% 性能提升**。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### vfio: introduce vfio-cxl to support CXL type-2 accelerator passthrough
- https://lore.kernel.org/all/20251209165019.2643142-1-mhonap@nvidia.com
- 该 RFC v2 系列引入 vfio-cxl-core，支持 CXL Type-2 加速器直通。在复用 vfio-pci 的基础上，补齐 CXL 特有初始化、复位、DVSEC/MMIO 仿真、HDM 解码器与 CXL region 映射等能力，并提供用户态接口与示例变体驱动。目标是为 QEMU/KVM 提供可审查、可扩展的 Type-2 设备直通基础设施。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### gpu: nova-core: Enable booting GSP with vGPU enabled
- https://lore.kernel.org/all/20251206124208.305963-1-zhiw@nvidia.com/
- 该系列为 nova-core 提出 RFC，目标是在启用 vGPU 的情况下启动 GSP，这是上游 vGPU 支持的重要里程碑。它基于最新 drm-rust-next，并依赖已合并的 GSP 启动功能及模块参数支持，用于在其他依赖尚未就绪前验证基本 GSP 启动流程。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: Introduce verifier test oracle
- https://lore.kernel.org/all/cover.1765158924.git.paul.chaignon@gmail.com/
- 该补丁集为 BPF 引入“验证器测试预言机”，用于让模糊测试更容易发现验证器的错误（尤其是静默的假阴性）。机制是在验证关键点保存寄存器/栈信息，运行时与真实值比对，不一致即发出警告。当前实现支持寄存器范围检查，可扩展到栈和 JIT，存在一些编码、子程序支持和触发点精度等待讨论的问题。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: Add wakeup_source iterators
- https://lore.kernel.org/all/20251204025003.3162056-1-wusamuel@google.com
- 该补丁集为 wakeup_source 引入 BPF 迭代器，解决通过 sysfs/debugfs 查询大量 wakeup sources 效率低且不安全的问题。补丁提供两类迭代器：标准 BPF iterator（通过 BPF link 遍历）与 open-coded iterator（在 BPF 程序中直接使用），均基于 wakeup_sources_walk_* API 高效遍历 wakeup_source 列表。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Compiler-Based Context
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认
#### and Locking-Analysis
- https://lore.kernel.org/all/20251120145835.3833031-2-elver@google.com
- 该系列补丁为内核引入 **Clang 基于编译器的 Context Analysis（上下文/锁静态分析）**，用于在编译期检查锁等上下文是否正确持有。依赖 Clang 22，通过可选、逐步启用的方式让各子系统自行 opt-in，初期支持多种锁原语，并在部分子系统中验证，可在编译阶段发现锁规则违规，补充但不替代 Lockdep/KCSAN。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### vfio/nvgrace-gpu: Support huge PFNMAP and wait for GPU ready post reset
- https://lore.kernel.org/all/20251121141141.3175-1-ankita@nvidia.com/
- 该补丁为 vfio/nvgrace-gpu 增强两点：利用内核新增的 huge PFNMAP 支持，实现 huge_fault，使大页方式映射 Grace 系统上的巨量 GPU 内存；不对齐则回退到 PTE。在 GPU reset 后需等待 GPU 就绪再恢复映射，避免 Grace CPU 的推测访问产生 RAS 纠错事件，并将等待过程延后到首次缺页以摊平延迟。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；对应改动如「vfio/nvgrace-gpu: Add Blackwell-Next GPU readiness check」）

#### vfio/pci: Base support to preserve a VFIO device file across Live Update
- https://lore.kernel.org/all/20251126193608.2678510-1-dmatlack@google.com/
- 该系列为 **VFIO PCI** 增加基础能力，允许在 **Live Update** 期间安全保留并取回 VFIO 设备文件（FD），但不保证设备完整运行态的保留。它为后续 IOMMUFD 与 VFIO 设备状态的完整迁移铺路，并处理 BDF 稳定性、FLB 同步与检索等问题，附带完整自测用例。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### PCI/TSM: Enabling core infrastructure on AMD SEV TIO
- https://lore.kernel.org/all/20251202024449.542361-1-aik@amd.com/
- 该系列补丁为 **AMD SEV-TIO** 启用 **PCI/TSM 基础设施的第一阶段（IDE 加密）**。SEV-TIO 通过 TDISP 让客体可信地使用支持 TEE 的设备。补丁实现 TSM 基础框架、sysfs 接口，并可为 PCI 设备启用 IDE 加密，为后续安全 MMIO/DMA 与设备证明奠定基础。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### iommufd: Enable noiommu mode for cdev
- https://lore.kernel.org/all/20251201173012.18371-1-jacob.pan@linux.microsoft.com/
- 该补丁为 IOMMUFD 的 cdev 增加 **No-IOMMU 模式**，通过引入虚拟 IOMMU 驱动、IOVA→物理地址查询、页固定等机制，使无 IOMMU 设备获得与真实 IOMMU 类似的管理能力，并兼容 VFIO。解决页固定不可靠、无法获取物理地址等问题，提升用户态驱动可用性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Remove device private pages from physical address space
- https://lore.kernel.org/all/20251128044146.80050-1-jniethe@nvidia.com
- 该提案将 **device private pages 从物理地址空间移除**，改为使用独立的“设备私有地址空间”，避免物理地址不足和架构兼容性问题。通过引入“设备私有 PFN”，PTE 可区分普通 PFN 与设备私有 PFN，从而正确索引设备内存。补丁重构分配与映射逻辑，消除对 request_free_mem_region() 依赖，并为未来去 struct page 化铺路。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add support for providers with large rx buffer
- https://lore.kernel.org/all/cover.1764264798.git.asml.silence@gmail.com/
- 该补丁集为网卡和内存提供者增加“大型接收缓冲区”支持，可将 RX buffer 从传统4K扩展到32K等更大尺寸，以减少缓冲区数量、提升 GRO 效率并显著降低 CPU 开销（单流场景可提升约30%）。系列补丁新增内核基础设施并在 bnxt 中实现，驱动可按需启用，主要面向 zcrx/memory provider，不影响 fast-path API。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### seccomp: support nested listeners
- https://lore.kernel.org/all/20251201122406.105045-1-aleksandr.mikhalitsyn@canonical.com/
- 该补丁为 seccomp 增加 “嵌套监听器” 支持，使容器与沙箱可在已有监听器之上再安装监听器，解决嵌套 LXC 等场景需求。为保证性能，在 seccomp 热路径中使用栈上静态数组，并将每条过滤链的监听器数限制为最多 8 个。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### SEV-SNP Unaccepted Memory Hotplug
- https://lore.kernel.org/all/20251125175753.1428857-1-prsampat@amd.com/
- 该系列为 SEV SNP 机密虚拟机增加对 “未接受内存” 的热插拔/热拔支持。通过将内存位图与原未接受表解耦，使内核可在热插拔时管理新内存并在热拔时恢复页状态。支持 eager/lazy 接受模式，并处理热拔期间共享状态导致的 pvalidate 冲突问题，实现机密 VM 的动态扩容。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Tracefs support for p KVM
- http://lore.kernel.org/all/20251202093623.2337860-1-vdonnefort@google.com
- 该系列为 pKVM 引入 tracefs 支持，提供远程事件与远程 ring-buffer 机制，使内核可读取由受保护模式下的 hypervisor 生成的跟踪数据。包含远程 ring-buffer 接口、tracefs 新的 trace_remote 子系统、简化版 ring-buffer、REMOTE_EVENT / HYP_EVENT 事件机制，并最终让 pKVM 可通过 tracefs 调试与分析。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2025年 第11期 (Start From 2025/11/01)

#### block: Enable proper MMIO memory handling for P2P DMA
- https://lore.kernel.org/all/20251114-block-with-mmio-v5-0-69d00f73d766@nvidia.com
- 该补丁改进块层与 NVMe 对 MMIO 内存的处理，使经主桥的 P2P DMA 能正确标记为 MMIO，避免错误的缓存同步、DMA 映射/解映射及 IOMMU 配置问题。核心是 NVMe 迁移至 dma_map_phys，并在块层正确走 MMIO 流程。
- 主线状态：✅ 已进入 mainline（commit 引用了本系列 Link）

#### gpu: nova-core: add Turing support
- https://lore.kernel.org/all/20251114233045.2512853-1-ttabi@nvidia.com/
- 该补丁集为 Turing GPU 增加 GSP-RM 预启动支持，并部分支持 GA100（实验性）。主要更新包括：新增非安全 IMEM 处理、调整 Turing 固件头解析、支持 tu10x 签名段、加入 Turing 专用寄存器、区分 Falcon 行为到 HAL、处理不同 FWSEC 描述符、对齐 LIBOS 参数结构，以及因无 DMA 改用 PIO 加载固件。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Memory Controller eBPF support
- https://lore.kernel.org/all/cover.1763457705.git.zhuhui@kylinos.cn/
- 该系列提议为内存控制器加入 eBPF 支持，让用户可在运行时定制内存管理策略。通过在 try_charge_memcg() 中加入 eBPF hook，允许实现自定义计费/回收逻辑，支持动态策略、监控与实验。补丁包括核心实现、自测及示例程序，强调零负担开销与安全可控性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### BTF performance optimizations with permutation and binary search
- https://lore.kernel.org/all/20251106131956.1222864-1-dolinux.peng@gmail.com/
- 该补丁系列通过引入类型排列与二分查找，将BTF类型查找性能提升约1785倍；核心改进包括新增 `btf__permute()` 支持类型重排、实现内核与用户态二分查找及懒验证机制，并提供自测用例验证一致性。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；commit 引用了本系列 Link）

#### KVM: x86: Support APX feature for guests
- https://lore.kernel.org/all/20251110180131.28264-1-chang.seok.bae@intel.com/
- 该系列补丁为 KVM x86 引入对 Intel APX 的初步支持，增加16个扩展寄存器（R16–R31），完善VMCS字段解析、指令模拟器REX2解码、统一GPR访问接口，并分四部分实现寄存器访问、VMX扩展、指令仿真与特性暴露。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched/kvm: Semantics-aware vCPU scheduling for oversubscribed KVM
- https://lore.kernel.org/all/20251110033232.12538-1-kernellwp@gmail.com/
- 该补丁系列为超分配KVM引入语义感知vCPU调度，通过“vCPU去加速器”和“IPI感知定向让渡”优化yield_to()，减少锁竞争与自旋等待，显著提升多VM并发性能，最高提高约47%，且无需修改Guest系统。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Specific Purpose Memory NUMA Nodes
- https://lore.kernel.org/all/20251112192936.2574429-1-gourry@gourry.net/
- 该补丁提议在内核中引入“专用内存（SPM）NUMA节点”，通过新增 `GFP_SPM_NODE`、`MHP_SPM_NODE` 等机制，将特定用途内存与系统RAM隔离，支持如ZSWAP等组件独占分配，改进mempolicy与cpuset在特殊内存管理中的局限。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### xfs: single block atomic writes for buffered IO
- https://lore.kernel.org/all/cover.1762945505.git.ojaswin@linux.ibm.com/
- 该补丁为 XFS 引入基于 iomap 的单块原子写支持，确保缓冲IO在页对齐下实现全成败一致性，并通过固定用户页与子页级原子写跟踪机制消除短写与块页限制，提升数据一致性与可靠性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### io: add io_pgtable abstraction
- https://lore.kernel.org/all/20251112-io-pgtable-v3-1-b00c2e6b951a@google.com/
- 该补丁引入通用 io_pgtable 抽象，供 Tyr GPU 驱动在用户态映射变化时创建或修改页表，简化GPU地址空间管理；基于Rust封装底层结构以适配非引用计数类型。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Introduce 128-bit IO access
- https://lore.kernel.org/all/20251112015846.1842207-1-huangchenghai2@huawei.com/
- 该补丁系列引入通用128位IO访问接口，以支持海思加密设备在物理与虚拟功能间进行128位原子MMIO操作，并在不支持原子指令的架构上提供非原子回退实现。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/ksw: Introduce KStackWatch debugging tool
- https://lore.kernel.org/all/20251110163634.3686676-1-wangjinchao600@gmail.com/
- 该补丁集引入 KStackWatch 工具，用硬件断点实时检测内核栈破坏，自动化定位如 CVE-2025-22036 等难复现问题，具低开销、可配置、多架构支持，显著提升内核栈错误调试效率。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched_ext: Improve bypass mode scalability
- https://lore.kernel.org/all/20251109183112.2412147-1-tj@kernel.org/
- 该补丁集优化 sched_ext 的 bypass 模式，在多核高并发下改用每CPU DSQ消除锁竞争，并新增定时负载均衡与即时中断机制，解决任务集中与活锁问题，大幅提升可扩展性与稳定性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Introduce ring flexible placement
- https://lore.kernel.org/all/cover.1762447538.git.asml.silence@gmail.com/
- 该补丁集引入环形缓冲区灵活放置机制，允许用户自定义SQ/CQ环及头部在内存区域中的偏移布局，减少填充浪费、优化缓存利用，并支持初始化阶段直接注册内存区域。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Documentation: Provide guidelines for tool-generated content	
- https://lore.kernel.org/all/20251105231514.3167738-1-dave.hansen@linux.intel.com/
- 该补丁为开发者提供使用AI等自动化工具参与内核开发的指导文档，重申应透明披露工具使用情况，保持可审查性，并遵循已有最佳实践，无新增规则。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「Documentation: Provide guidelines for tool-generated con」）

#### bpf: magic kernel functions
- https://lore.kernel.org/all/20251029190113.3323406-1-ihor.solodrai@linux.dev
- 该补丁系列提出“magic kfuncs”机制，使 BPF 内核函数（kfunc）可隐式接收由 verifier 提供的参数，如 bpf_prog_aux。实现上修改 pahole 的 BTF 编码，为每个函数生成含/不含隐式参数的两种声明；通过 KF_MAGIC_ARGS 标志与“__magic”注解标识此类参数，并以 BTF_ID_LIST 建立高效查表机制。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；commit 引用了本系列 Link）

#### net: devmem: improve cpu cost of RX token management
- https://lore.kernel.org/all/20251104-scratch-bobbyeshleman-devmem-tcp-token-upstream-v6-0-ea98cf4d40b3@meta.com/
- 该补丁系列通过新增套接字选项 **SO_DEVMEM_AUTORELEASE**，优化 RX token 管理以降低 CPU 开销。新机制使用 niov 数组和 uref 字段取代 xarray 分配器，使每个接收线程 CPU 利用率提升约 13%。其他基于哈希表和 RCU 的方案未带来改进。优化默认启用，已在 kperf 与 nccl 测试中验证效果。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2025年 第10期 (Start From 2025/10/01)

#### PCI: trace: Add a RAS tracepoint to monitor link speed changes
- https://lore.kernel.org/all/20251025114158.71714-1-xueshuai@linux.alibaba.com/
- 该补丁集新增了 PCI 热插拔和 PCIe 链路跟踪点，用于分析硬件健康状况。热插拔事件和意外链路断开会影响系统性能与可靠性，而链路速率下降通常预示设备故障、物理层问题或配置错误。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；对应改动如「PCI: trace: Add RAS tracepoint to monitor link speed cha」）

#### Initial DMABUF support for iommufd
- https://lore.kernel.org/all/0-v1-64bed2430cdb+31b-iommufd_dmabuf_jgg@nvidia.com
- 该补丁系列为 iommufd 引入初始的 DMABUF 支持，目前仅适用于 VFIO 的 DMABUF 导出器。它增强了 IOMMU_IOAS_MAP_FILE，使其可识别 DMABUF 文件描述符，用于在 iommufd 管理的域中安全映射设备内存。相比 VFIO type1 的直接 PFN 提取方式，新机制通过可撤销的 DMABUF 提高安全性，并为未来支持 GPU、DPDK、SPDK 等场景奠定基础。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### xfs: autonomous self healing of filesystems
- https://lore.kernel.org/all/176117744372.1025409.2163337783918942983.stgit@frogsfrogsfrogs/
- 该补丁集为 XFS 引入文件系统自愈功能，通过匿名文件接口向用户空间实时报告健康事件，如元数据损坏、I/O 错误和卸载等。具有 CAP_SYS_ADMIN 权限的程序可读取事件，并由新建的 systemd 管理守护进程自动执行修复，实现文件系统的自主检测与恢复。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### ext4: enable block size larger than page size
- https://lore.kernel.org/all/20251025032221.2905818-1-libaokun@huaweicloud.com/
- 该补丁系列为 EXT4 启用大于页面大小的块（Large Block Size）支持，修复除零、位移错误等问题，并优化挂载选项处理。测试显示：4K 性能无明显变化，BIO 写入性能较 bigalloc 提升约 50%，但 DIO 写入在大块下下降约 30%。性能差异主要源于块分配时 CRC 计算开销增加。未来计划继续优化 LBS 块分配性能。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/damon: support pin-point targets removal
- https://lore.kernel.org/all/20251016214736.84286-1-sj@kernel.org/
- 该补丁提案为 DAMON 内存监控框架增加“精确目标移除”功能。原机制只能整体替换目标列表，无法单独删除特定监控目标。新方案通过在内核 API 中引入 `obsolete` 字段及对应的 sysfs 接口，使用户能在不停止 DAMON 的情况下，精准移除单个失效目标，节省内核内存并保持其他监控数据。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rtla/timerlat: Add --bpf-action option
- https://lore.kernel.org/all/20251017144650.663238-1-tglozar@redhat.com/
- 该补丁为 **rtla-timerlat** 增加 `--bpf-action` 选项，允许在延迟阈值超限时执行用户自定义的 **BPF 程序**。通过 `bpf_tail_call()` 与内置采样程序衔接，可实现内核态数据收集或直接向用户态发送信号，增强延迟监控灵活性，需与相关补丁协调合并。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；对应改动如「rtla/timerlat: Add --bpf-action option」）

#### sched: Rewrite MM CID management
- https://lore.kernel.org/all/20251015164952.694882104@linutronix.de
- 该补丁系列重写了 **MM CID（内存上下文ID）管理机制**，解决当前实现中 CID 空间压缩与任务调度关联复杂、效率低下的问题。新设计根据任务数与允许 CPU 数动态切换“按任务”与“按CPU”模式，仅在 fork、exit、affinity 变化时更新，大幅减少锁竞争和调度开销。测试显示在高并发场景下性能提升显著，代码更简洁、可维护性更高。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched_ext: lockless peek operation for DSQs
- https://lore.kernel.org/all/20251015015712.3996346-1-rrnewton@gmail.com
- 该补丁为 Linux 的 sched_ext 调度器增加了对调度队列（DSQ）的无锁 peek 操作，可高效查看队首元素而无需加锁或创建迭代器。测试表明在多核 CPU（如 Ryzen Threadripper 与 EPYC）上可显著提升性能，特别是在使用每 CPU DSQ 并比较最小 vruntime 时。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: x86: selftests: add L1TF exploit test
- https://lore.kernel.org/all/20251013-l1tf-test-v1-0-583fb664836d@google.com/
- 新增 KVM / x86 L1TF 利用自测，在 Skylake 上验证复现。条件性 L1D 刷新可能使测试失效，需改进评估条件刷新。旨在为 Address Space Isolation 供端到端测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Implement DMA Guard Pages
- https://lore.kernel.org/all/20251012125218.45c5f972.michal.pecio@gmail.com/
- 该提案引入 DMA Guard Pages，在 IOMMU 设备的连续 DMA 映射间插入未映射页，防止越界访问影响其他内存。作者为调试设备自制实现，认为有助于提高驱动开发与系统可靠性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### dma-buf: heaps: Create a CMA heap for each CMA reserved region
- https://lore.kernel.org/all/20251013-dma-buf-ecc-heap-v8-0-04ce150ea3d9@kernel.org/
- 该补丁为每个 CMA 保留内存区创建独立 dma-buf 堆，用于用户空间从特定内存区域分配缓冲，支持无 ECC 区域等场景。方案避免修改设备树，简化设计，并有助于后续在 DRM/KMS 与 v4l2 中支持 cgroup 管理。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Confidential VMBus
- https://lore.kernel.org/all/20251008233419.20372-1-romank@linux.microsoft.com/
- 该补丁集为 Hyper-V 虚拟机引入“机密 VMBus”，支持在加密内存环境中安全传输设备数据，使主机和管理程序无法访问来宾数据，仅在来宾同意时共享。方案兼容旧系统，依赖 paravisor（如 OpenHCL）实现，适用于支持 SEV-SNP、TDX 等硬件的机密来宾。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### net: optimize TX throughput and efficiency
- https://lore.kernel.org/all/20251006193103.2684156-1-edumazet@google.com/
- 该补丁集通过在 `__dev_queue_xmit()` 中用无锁链表（llist）替换自旋锁机制，显著降低 qdisc 锁竞争，仅允许单 CPU 自旋，其余直接入队。此优化在高负载发送场景下提升传输效率约300%，实现更高包速率与更低 CPU 占用，并包含若干相关修复与结构调整。
- 主线状态：✅ 已进入 mainline（约 v6.19-rc1；commit 引用了本系列 Link）

#### Introduce PCI Configuration Space Cache (PCSC)
- https://lore.kernel.org/all/cover.1759312886.git.epetron@amazon.de/
- 该补丁集引入 **PCI 配置空间缓存（PCSC）**，在虚拟化环境中缓存 PCI 配置寄存器以减少硬件访问延迟。其核心是透明缓存层，拦截读写并采用写失效策略，保证一致性与性能。支持 kexec 持久化，通过 KHO 保存缓存数据，在新内核恢复时显著缩短虚拟机启动时间（最高提速约50%），命中率可达81%，兼容现有驱动且可完全禁用。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### liveupdate: Rework KHO for in-kernel users
- http://lore.kernel.org/all/20251007033100.836886-1-pasha.tatashin@soleen.com
- 该补丁系列重构 KHO 框架，以支持内核内用户（如即将到来的 LUO）。主要改动包括移除通知链，改用直接注册 API，使客户端可灵活管理保留状态；导出 `kho_finalize()` 与 `kho_abort()`；将 debugfs 接口设为可选；新增取消保留内存的接口并修复中止路径错误；同时将相关代码迁入 `kernel/liveupdate/` 目录。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/userfaultfd: modulize memory types
- https://lore.kernel.org/all/20250926211650.525109-1-peterx@redhat.com/
- 该补丁系列重构了 **userfaultfd** 内部机制，引入通用接口 **vm_uffd_ops**，使内核模块可独立支持不同类型内存（如 shmem、hugetlbfs）的 userfaultfd 功能，而无需修改 mm/ 子系统。此改进为未来 guest-memfd 等特性铺路，不涉及功能变更，仅模块化代码结构并优化接口设计，性能无明显差异。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### iommu: Add live update state preservation
- https://lore.kernel.org/all/20250928190624.3735830-1-skhawaja@google.com/
- 该RFC补丁系列为IOMMU在内核**热更新（live update）**中引入状态保存机制，以Intel VT-d为示例实现。其目标是在系统更新时保持设备的DMA映射和IOMMU上下文不丢失，实现虚拟机设备无缝迁移。当前版本仅保存IOMMU根表和上下文表，未来将支持页表、PASID等完整状态。方案依托Live Update Orchestrator协调iommufd与IOMMU驱动，计划采用“热交换（hotswap）”方式恢复，已通过QEMU+VT-d环境初步验证。
- 主线状态：✅ 已进入 mainline（约 v6.19-rc1；commit 引用了本系列 Link）

#### drm: Optimize page tables overhead with THP
- https://lore.kernel.org/all/20250929200316.18417-1-loic.molinari@collabora.com/
- 该补丁集优化 DRM 驱动在启用透明大页（THP）时的页表开销。通过为 GEM 对象增加大页缺页处理器，在可能情况下建立 PMD/PUD 映射，并引入新的 `get_unmapped_area` 接口以优化虚拟地址对齐。同时提供 shmem 辅助函数创建和释放大页 tmpfs 挂载点，并在 i915、V3D、Panfrost、Panthor 等驱动中启用可选 THP 支持，显著提升显存映射效率。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Runtime TDX Module update support
- https://lore.kernel.org/all/20251001025442.427697-1-chao.gao@intel.com/
- 该补丁集为 Intel TDX 引入**运行时模块更新机制**，允许在不中断运行的 TDX 客户机情况下更新 TDX Module，避免重启带来的停机时间。通过 `fw_upload` 接口加载用户态选择的更新镜像，并在 `stop_machine()` 环境中执行以确保安全。更新仅限 Z 级版本变更，内核提供模块版本信息供用户态决策。此机制提升 TDX 系统的可维护性与安全可控性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### expand mmap_prepare functionality, port more users
- https://lore.kernel.org/all/cover.1758135681.git.lorenzo.stoakes@oracle.com
- 该补丁系列旨在扩展并推广 `mmap_prepare` 接口，以取代已弃用的 `f_op->mmap` 钩子，避免驱动和文件系统直接操作未初始化的 VMA 带来的安全与复杂性问题。新机制引入“mmap动作”概念，可在 `mmap_prepare` 阶段动态决定执行普通映射、PFN 重映射或 I/O 重映射，并支持前后处理钩子。补丁同时改造多个子系统（如 shmem、hugetlbfs、devdax、/dev/mem 等）以统一迁移至该接口，强化内存映射安全与可维护性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2025年 第09期 (Start From 2025/09/01)

#### parker: PARtitioned KERnel
- https://lore.kernel.org/linux-pm/20250923153146.365015-1-fam.zheng@bytedance.com/
- Parker 提议在单机上同时运行多个 Linux 内核实例，无需传统虚拟化。通过 CPU、内存和设备分区，每个内核独立运行，适合高核心数场景以提升可扩展性。Boot Kernel 负责资源分配，其余为 Application Kernel。实现基于 kexec 与 kernfs，支持差异化调优。当前缺乏隔离，单实例故障可能影响全机。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### memcg: Support per-memcg KSM metrics
- https://lore.kernel.org/all/20250921230726978agBBWNsPLi2hCp9Sxed1Y@zte.com.cn/
- 该补丁集为 memcg 引入容器级 KSM 统计支持。原本 cgroup 无法观测 KSM 行为，现通过在 `memory.stat` 中增加统计项实现，而非新接口。实现方式是遍历 memcg 内所有进程并汇总其 ksm\_rmap\_items 等计数器，避免在 ksmd 操作页时更新枚举项所带来的计数不准与内存开销问题，从而为容器提供准确的 KSM 指标观测能力。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: Improve mlock tracking for large folios
- https://lore.kernel.org/all/20250919124036.455709-1-kirill@shutemov.name/
- 该补丁集改进大页 folio 的 mlock 统计，减少 `/proc/meminfo` 中 Mlocked 内存低估问题。前两补丁修复 mlock\_vma\_folio 与解映射间的竞争，避免部分映射页错误进入不可回收 LRU。后续补丁在 unmap、fault、rmap 环节增加逻辑，确保大页能完整上锁，从而提升统计精度与一致性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: hugetlb: allocate frozen gigantic folio
- https://lore.kernel.org/all/20250918132000.1951232-1-wangkefeng.wang@huawei.com/
- 该补丁集优化了 hugetlb 巨型 folio 的分配效率，将 200×1G 分配耗时由 2.124s 降至 0.429s。通过新增 `alloc_contig_frozen_pages()` 和 `cma_alloc_frozen_compound()`，避免页引用计数的原子操作，并在 hugetlb 中使用新助手实现冻结分配，简化 `alloc_gigantic_folio()`。v2 中进一步清理接口并引入 HPAGE\_PUD\_ORDER 调试支持。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；对应改动如「mm: hugetlb: allocate frozen pages for gigantic allocati」）

#### ext4: optimize online defragment
- https://lore.kernel.org/all/20250923012724.2378858-1-yi.zhang@huaweicloud.com/
- 该补丁集优化 ext4 在线碎片整理，将原先基于 PAGE\_SIZE 的 move\_extent\_per\_page() 替换为支持大 folio 的 mext\_move\_extent()，显著提升效率并减少与 buffer\_head 的耦合。补丁还修复边界与检查问题，引入序列计数器，重构参数校验，统一代码风格以契合 iomap，为后续文件系统缓冲 I/O 向 iomap 转换奠定基础，并在性能测试中展现显著提升。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rv: Add Hybrid Automata monitor type, per-object and deadline monitors
- https://lore.kernel.org/all/20250919140954.104920-1-gmonaco@redhat.com/
- 该补丁集为 RV 框架引入多项新特性：清理 DA monitor 宏；支持混合自动机，扩展定时自动机以验证环境变量约束；实现通用 per-object monitor，可按对象标识管理监控数据；新增 deadline 相关监控器（throttle、nomiss）用于验证调度时序。补丁还统一事件处理、改进定时器机制、扩展模型和脚本，增强对任务切换和跨 CPU 事件的支持。
- 主线状态：✅ 已进入 mainline（约 v7.1；对应改动如「rv: Add Hybrid Automata monitor type」）

#### Compiler-Based Capability
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认
#### and Locking-Analysis
- https://lore.kernel.org/all/20250918140451.1289454-1-elver@google.com/
- 该补丁集在内核中引入基于编译器的 Capability Analysis，用于静态检测锁与能力的获取和释放，提升锁安全性。它借鉴 Clang Thread Safety Analysis，支持多种同步原语，并允许子系统选择性启用，避免一次性全局修改。该方案能在编译期发现潜在锁规则违规，作为 Lockdep、KCSAN 等动态工具的补充，已有部分内核子系统率先应用。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched_ext: Implement cgroup sub-scheduler support
- https://lore.kernel.org/all/20250920005931.2753828-1-tj@kernel.org
- 该补丁集为 sched\_ext 引入 cgroup 子调度器支持，允许在 cgroup 层级中嵌套多个调度器，适用于多租户和多样化工作负载场景。相比依赖 cpuset 的硬分区，该方案更灵活，支持 BPF 驱动的动态 CPU 分配、延迟优化、带宽公平及缓存局部性提升。实现提供最多四级调度层级，子调度器可独立启停，减少全局影响，初步展示了层级调度的核心机制与示例。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kernel: Introduce multikernel architecture support
- https://lore.kernel.org/all/20250918222607.186488-1-xiyou.wangcong@gmail.com
- 该补丁集提出多内核架构支持，允许单机上运行多个独立内核实例，各占用专属 CPU 核并共享硬件资源。其优势包括更强的故障隔离、安全性提升、资源利用率优化及零停机内核切换。实现基于 kexec，提供动态 kimage 管理、跨内核 IPI 通信框架、x86 启动机制及 /proc 接口。此为 RFC 版本，旨在建立基础框架并收集社区反馈，未来可支持实时内核与通用内核并行等新场景。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### fuse: containerize ext4 for safer operation
- https://lore.kernel.org/all/20250916000759.GA8080@frogsfrogsfrogs/
- 该提案通过 fuse+iomap 将 ext4 文件系统移至用户态运行，实现容器化文件系统服务，降低内核元数据解析带来的安全风险。实验表明性能接近内核驱动，大部分 fstests 已通过。实现了无特权 systemd 服务运行、部分 VFS 标志支持，但仍存在 journal 缺失、EOF 处理等问题，后续需优化设计与代码审查。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### PCI: Resizable BAR improvements
- https://lore.kernel.org/all/20250911075605.5277-1-ilpo.jarvinen@linux.intel.com/
- 该补丁系列优化 PCI 可调整 BAR 支持，将相关代码从 pci.c 独立到 rebar.c，使结构更清晰。新增 API 由内核统一处理 Resizable BAR 操作，简化驱动实现，并将 BAR 大小位掩码改为 u64 以符合 PCIe 规范扩展。补丁已在 sysfs、i915 与 xe 驱动中测试验证，后续可独立合并进主线，减少冲突并提升可维护性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### cxl: ACPI PRM Address Translation Support and AMD Zen5 enablement
- https://lore.kernel.org/all/20250912144514.526441-1-rrichter@amd.com/
- 该补丁集在 CXL 驱动中引入 ACPI PRM 地址转换支持，并为 AMD Zen5 平台启用。当前 CXL 假设 HPA=SPA，但在部分系统中二者不同，需要转换。补丁通过回调机制实现 HPA 向父端口 SPA 转换，并在 region 结构中保存结果，仅支持解码器自动发现。此改进简化实现，去除平台特定代码，并作为后续文档更新的基础。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；对应改动如「Documentation/driver-api/cxl: ACPI PRM Address Translati」）

#### Make KHO Stateless
- https://lore.kernel.org/all/20250917025019.1585041-1-jasonmiu@google.com/
- 该补丁系列将 KHO 从基于 xarray 的元数据追踪与序列化机制转为页表式结构，直接传递给下一个内核。此改进消除序列化和状态机流程（弃用 finalize/abort），通过 FDT 传递根页表地址以重建保留内存。主要变化包括引入新页表结构、移除旧实现、更新 memblock 接口及删除通知系统。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### paravirt CPUs and push task for less vCPU preemption
- https://lore.kernel.org/all/20250910174210.1969750-1-sshegde@linux.ibm.com
- 该系列补丁 v3 版本针对半虚拟化 CPU 与任务推送机制进行改进，目标是减少 vCPU 被抢占的情况。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### objtool,livepatch: klp-build livepatch module generation
- https://lore.kernel.org/all/cover.1758067942.git.jpoimboe@kernel.org
- 该补丁系列在 objtool 中加入新功能，并提供 klp-build 脚本以自动生成 livepatch 模块，取代早期的 kpatch-build。其优势包括更简洁的实现、与 LTO/IBT 等兼容、减少代码冗余并去除 out-of-tree hack。流程为：构建内核、应用补丁、利用 objtool 分析差异函数并生成中间对象，最终链接成 livepatch 模块。此方案吸收 kpatch 十余年经验，提升可维护性与内核主线集成度。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KFuzzTest: a new kernel fuzzing framework
- https://lore.kernel.org/all/20250901164212.460229-1-ethan.w.s.graham@gmail.com/
- 该补丁系列提出 KFuzzTest，一种轻量级内核模糊测试框架，用于在内核中直接测试底层函数，避免依赖用户态或桩化。其核心包括宏定义快速生成测试、二进制输入格式序列化复杂结构体、以及 ELF 元数据便于发现和分析。KFuzzTest 已在 syzkaller 中验证有效，能快速触发漏洞。V2 增加工具、文档与示例，并调整目录结构，强调独立发展，同时兼顾未来与 KUnit 的潜在融合。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/ksw: Introduce real-time KStackWatch debugging tool
- https://lore.kernel.org/20250912101145.465708-1-wangjinchao600@gmail.com
- 该补丁系列引入轻量级内核调试工具 KStackWatch，用于实时检测内核栈损坏。其通过硬件断点结合 kprobe/fprobe，监控栈 canary 或局部变量，在损坏发生瞬间定位源头，避免仅看到崩溃结果。工具开销小、配置简单，支持递归深度过滤，并附带测试模块和脚本验证有效性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### tracing: wprobe: Add wprobe for watchpoint
- https://lore.kernel.org/all/175785897434.234168.6798590787777427098.stgit@devnote2/
- 该补丁集第4版引入 wprobe（watch probe），用于跟踪内存访问事件，并可与事件触发器结合实现对动态分配对象的访问监控。wprobe 用法与其他 probe 类似，支持按地址或符号设置读写监控，并通过 set/clear_wprobe 触发器在对象生命周期内动态设置或清除监控。示例展示了在文件系统 dentry 结构体的创建与销毁过程中对内存访问的追踪效果。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: x86: Improve the handling of debug exceptions during instruction emulation
- https://lore.kernel.org/all/cover.1757416809.git.houwenlong.hwl@antgroup.com
- 该补丁集改进 **KVM x86 指令仿真中的调试异常处理**。目前仅考虑 DR7，导致 `DR6.BD` 在仿真中失效，且用户态与来宾调试逻辑重复。补丁引入统一函数 `kvm_inject_emulated_db()` 合并检查与处理，确保开启调试时退出用户态，否则注入 #DB 异常。同时修复单步 #DB 未考虑中断影子的问题，以避免 VMX 进入失败或 `MOV SS` 抑制失效。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；commit 引用了本系列 Link）

#### sched/fair: Distributed nohz idle CPU tracking for idle load balancing
- https://lore.kernel.org/all/20250904041516.3046-1-kprateek.nayak@amd.com
- 该补丁系列提出在 **CFS 调度器**中将全局 nohz 空闲 CPU 跟踪改为分布式 per-LLC 机制，以降低原全局变量原子操作带来的性能瓶颈。实现通过在每个 sd\_llc\_shared 维护 cpumask，并在必要时更新全局统计，仅在边界条件触发原子操作。测试显示多数基准性能持平或小幅提升，个别差异源于运行波动，无显著回归，适合作为 push-based 负载均衡的基础优化。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched/fair: Optimize cfs_rq and sched_entity allocation for better data locality
- https://lore.kernel.org/all/20250903194503.1679687-1-zecheng@google.com/
- 该补丁集优化 **CFS 调度器**内存布局，将 `cfs_rq` 与 `sched_entity` 在每 CPU 上联合分配，替代原有指针数组设计，以提升数据局部性并减少缓存未命中。实测结果显示 AMD 平台 LLC 缓存未命中率下降约 8–12%，Intel 平台下降约 28–32%，并带来最高 25% 的 IPC 提升。其他常见基准测试无明显性能回退。补丁主要包括联合分配、移除指针数组及使用 per-cpu 分配器三部分。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；对应改动如「sched/fair: Co-locate cfs_rq and sched_entity in cfs_tg_」）

#### Untrusted Data API
- https://lore.kernel.org/all/20250814124424.516191-1-lossin@kernel.org/
- 该补丁集主要引入 **Untrusted Data API**，以便在内核中提供基础支持。作者表示这是 v3 的重发版，基于 v6.17-rc1 更新，并结合 Alice 的 iov\_iter 补丁。建议本周期先合并前两部分，尽快让社区尝试；第三个补丁的验证逻辑尚需完善。作者认为字段投影功能对 API 实用性关键，已在 Rust 上游推动相关实验并提交 2025H2 项目目标。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### unwind_deferred: Implement sframe handling
- https://lore.kernel.org/all/20250827201548.448472904@kernel.org/
- 该补丁系列实现对 ELF 文件中 SFrame 区段的解析，用于替代依赖帧指针的用户态栈回溯。SFrame 提供类似 ORC 的机制，解决性能开销大、编译器差异及部分架构无统一格式的问题。由于需在安全上下文加载 SFrame，本实现将栈回溯延迟到合适时机执行，从而支持 perf 等工具可靠获取用户态调用栈。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Direct Map Removal Support for guest_memfd
- https://lore.kernel.org/all/20250828093902.2719-1-roypat@amazon.co.uk/
- 该补丁系列为 guest_memfd 增加移除宿主机内核 direct map 的支持，以缓解 Spectre 类推测执行攻击，保护虚拟机内存安全。通过 `GUEST_MEMFD_FLAG_NO_DIRECT_MAP` 标志启用，KVM 可在无 direct map 的情况下仍通过用户态映射访问客户机内存。实现涵盖 ioctl 扩展、自测增强，并已在 Firecracker 分支验证，显著提升虚拟化安全性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### vsock: add namespace support to vhost-vsock
- https://lore.kernel.org/all/20250827-vsock-vmtest-v5-0-0ba580bede5b@meta.com/
- 该补丁为 vhost-vsock 与 loopback 引入 namespace 支持，新增 local 与 global 两种模式：local 完全隔离，global 完全共享（保持原行为）。模式通过 `/proc/sys/net/vsock/ns_mode` 设置，按 netns 生效且仅可写一次。支持不同命名空间独立配置，便于隔离或共享 CID 资源。补丁同时完善了自测用例，22 项测试全部通过。
- 主线状态：✅ 已进入 mainline（commit 引用了本系列 Link）

#### virtio_net: Add ethtool flow rules support
- https://lore.kernel.org/all/20250827183852.2471-1-danielj@nvidia.com/
- 该补丁系列为 virtio\_net 引入基于 virtio flow filter 规范的 ethtool 流规则支持，使用户可通过 ethtool 配置数据包过滤，实现定向至指定接收队列或丢弃。实现涵盖以太网、IPv4/IPv6、TCP/UDP 等流规则，并支持规则增删查管理，显著增强 virtio\_net 在流量分流与包处理上的灵活性与可控性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2025年 第08期 (Start From 2025/08/01)

#### Add support for long task name
- https://lore.kernel.org/all/20250821102152.323367-1-bhupesh@igalia.com/
- 该补丁集旨在为 Linux 内核任务名提供 64 字节扩展支持（TASK_COMM_EXT_LEN），解决现有 16 字节 TASK_COMM_LEN 导致任务名被截断的问题，尤其在调试和游戏平台场景下更实用。实现方式是在 `task_struct` 中临时引入 `comm_str`，保持 ABI 向后兼容，原接口仍返回 16 字节，新的接口可支持完整 64 字节名称。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### dax/hmem, cxl: Coordinate Soft Reserved handling with CXL
- https://lore.kernel.org/all/20250822034202.26896-1-Smita.KoralahalliChannabasappa@amd.com/
- 该补丁集旨在解决 dax_hmem 与 CXL 在处理 Soft Reserved 内存区域时的长期冲突。当前重点在于协调两者行为，并讨论如何支持 DAX_CXL_MODE_REGISTER，但具体方案尚未确定。
- 主线状态：✅ 已进入 mainline（约 v7.1-rc1；对应改动如「dax/hmem, cxl: Defer and resolve Soft Reserved ownership」）

#### PCI/TSM: Core infrastructure for PCI device security
- https://lore.kernel.org/all/20250827035126.1356683-1-dan.j.williams@intel.com/
- 该补丁集为 PCI 设备安全（TDISP）建立核心基础设施，基于示例 TSM 驱动提供跨厂商通用实现，用于支持设备在 TEE 环境下的安全状态切换（UNLOCKED→LOCKED→RUN）。本版主要完成接口清理、文档修正和结构优化，并通过样例模块测试，为后续与厂商实现对接及主线合入奠定基础。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### PCI/TSM: TEE I/O infrastructure
- https://lore.kernel.org/all/20250827035259.1356758-1-dan.j.williams@intel.com/
- 该补丁集为 PCI/TSM 提供 TEE I/O 基础设施，支持设备在受信任虚拟机（TVM）中从 UNLOCKED→LOCKED→RUN 的安全状态切换，并协调驱动加载、MMIO 和 DMA 配置。新增绑定/解绑及请求接口，结合 samples/devsec 测试验证，实现设备被安全接纳至 TEE 的完整流程。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### cgroups: Add support for pinned device memory
- https://lore.kernel.org/all/20250819114932.597600-5-dev@lankhorst.se/
- 该补丁系列为 cgroups 增加固定设备内存支持，解决多 GPU 场景下 dma-buf 被驱逐到系统内存导致性能严重下降的问题。通过允许进程将关键缓冲区固定，避免长任务因内存驱逐被中断。实现上在 cgroup 层检查并限制固定内存使用量，调整 min/low 值计算，以确保层级内存分配公平与稳定。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### A subsystem for hot page detection and promotion
- https://lore.kernel.org/all/20250814134826.154003-1-bharata@amd.com/
- 该补丁集引入热页检测与提升子系统，统一收集底层访问信息并按 PFN 粒度判定“热页”，由内核线程批量迁移至高层内存。通过哈希表快速记录热页，并为目标节点维护最大堆按热度排序，解决以往扫描开销大和记录提取低效问题。API 保持不变，支持基于 IBS 和 PTE-A 的访问检测，未来计划优化热度指标、记录存储与迁移限速。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### iommu/amd: Introduce Nested Translation support
- https://lore.kernel.org/all/20250820113009.5233-1-suravee.suthikulpanit@amd.com/
- 该补丁系列为 AMD IOMMU 引入嵌套页表转换支持，结合宿主机页表 (v1) 与客户机页表 (v2)。驱动通过在设备表项配置宿主机页表根指针与客户机 CR3 根指针实现。宿主机页表由分配嵌套父域完成，客户机页表则通过相应接口利用 GCR3、GIOV、GLX 等参数配置和绑定设备。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rseq: Optimize exit to user space
- https://lore.kernel.org/all/20250813155941.014821755@linutronix.de
- 该补丁系列优化 rseq 代码，清理过时的 `rseq_event_mask` 逻辑，避免无意义的用户态退出处理，并修复关键区段在系统调用场景下的不当处理。同时引入新的掩码访问模型，降低 Spectre-V1 缓解带来的开销，带来显著性能提升（实测可达 25% 以上），为基于 rseq 的时间片扩展机制奠定基础。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### cgroup/cpuset: Enable runtime modification of
- https://lore.kernel.org/all/20250808151053.19777-1-longman@redhat.com/
- 该补丁集为 Linux cpuset 增强运行时修改隔离 CPU 功能，使 nohz\_full/rcu\_nocbs 等内核降噪机制可动态调整，减少对敏感任务的干扰，并通过 CPU 热插拔实现隔离切换。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Cache aware load-balancing
- https://lore.kernel.org/all/cover.1754712565.git.tim.c.chen@linux.intel.com/
- 该补丁集引入缓存感知负载均衡，通过监测进程驻留页数和线程数，避免不同数据任务聚集于同一LLC导致性能下降；默认仅在负载均衡时聚合任务，提供debugfs调节策略，优化Sapphire Rapids性能并减轻Milan回归。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add unified configuration for coding agents
- https://lore.kernel.org/all/20250809234008.1540324-1-sashal@kernel.org/
- 该补丁集为内核开发引入统一的AI编码助手配置与文档，重构README按角色提供指南，要求AI协助贡献加“Assisted-by”标注，并为多种主流编码助手提供统一配置引用。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### dibs 
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认
#### Direct Internal Buffer Sharing
- https://lore.kernel.org/all/20250806154122.3413330-1-wintera@linux.ibm.com/
- 该系列补丁引入了一个名为“dibs”（Direct Internal Buffer Sharing）的通用抽象层。它旨在将现有的 s390 ISM 和 SMC-D 等内部共享内存机制进行通用化和解耦。通过创建一个独立的 dibs 层，可以更清晰地分离功能，减少模块依赖，并为未来添加更多设备和客户端（如TTY）提供了可扩展的框架。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rust: page: implement BorrowedPage
- https://lore.kernel.org/all/20250804195023.150399-1-dakr@kernel.org/
- 该补丁为 Rust 语言的页面管理引入了 `BorrowedPage` 类型。目前 `Page` 总是独占其底层 `struct page`，但在某些情况下（如 vmalloc 分配），`struct page` 可能被其他实体拥有。`BorrowedPage` 正是为此类场景设计，支持共享所有权，以满足 `scatterlist` 抽象的需求，并在未来过渡到 `Ownable` 方案。
- 主线状态：✅ 已进入 mainline（约 v6.18-rc1；对应改动如「rust: page: implement BorrowedPage」）

#### Coverage deduplication for KCOV
- https://lore.kernel.org/all/20250731115139.3035888-1-glider@google.com/
- 该系列补丁为 KCOV 引入了一种覆盖率去重机制，以解决 `syzkaller` 等模糊测试工具中因用户空间缓冲区溢出导致覆盖率数据丢失的问题。该方法通过为每个覆盖回调分配唯一ID，并使用一个用户空间位图来记录已执行的代码，从而只将唯一的程序计数器（PC）写入跟踪缓冲区。这有效减少了溢出，提高了模糊测试的效率和覆盖率。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: Introduce deferred task context execution
- https://lore.kernel.org/all/20250806144554.576706-1-mykyta.yatsenko5@gmail.com/
- 该系列补丁引入了 BPF 程序 **延迟任务上下文执行** 的新机制。它允许 BPF 程序利用内核的 `task_work` 框架，在特定任务的上下文中调度可睡眠的子程序执行。这对于从不可睡眠环境（如 NMI）调度可睡眠函数非常有用，通过新的 `kfuncs` 和原子状态机来管理回调和确保并发安全。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### tracing: Show contents of syscall trace event user space fields
- https://lore.kernel.org/all/20250805192646.328291790@kernel.org/
- 该系列补丁增强了系统调用跟踪事件，使其能显示用户空间参数的具体内容。通过为每个CPU创建临时缓冲区，它实现了对用户空间内存的安全读取。当用户空间任务被调度时，一个计数器会更新，用于确保复制内存时的完整性。用户还可以在 `tracefs` 中配置复制内容的长度，从而在跟踪输出中直接看到更详细的系统调用参数信息。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add overwrite mode for bpf ring buffer
- https://lore.kernel.org/all/20250804022101.2171981-1-xukuohai@huaweicloud.com
- 该系列补丁为 BPF 环形缓冲区 添加了 覆盖模式。在传统模式下，缓冲区满时新事件会被丢弃，这可能导致重要的最新事件丢失。通过引入覆盖模式，当缓冲区满时，新的事件将自动覆盖掉最旧的事件，从而确保最新数据始终得到记录，这对于故障诊断等场景至关重要。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### RV: Linear temporal logic monitors for RT application
- https://lore.kernel.org/all/cover.1751634289.git.namcao@linutronix.de/
- 该系列补丁为实时应用引入了基于线性时序逻辑（LTL）的运行时验证（RV）监控器。针对实时应用中可能出现的延迟问题，如缺页错误或优先级反转，作者发现LTL比传统的确定性自动机更简洁、直观。该系列补丁清理了RV代码，添加了LTL监控器支持，并实现了两个具体的监控器来检测实时任务的缺页和潜在的睡眠延迟问题。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc1；对应改动如「Documentation/rv: Add documentation for linear temporal 」）

## 2025年 第07期 (Start From 2025/07/01)

#### Add Rust abstraction for Maple Trees
- https://lore.kernel.org/all/20250726-maple-tree-v1-0-27a3da7cb8e5@google.com/
- 本次更新为 Maple Trees 引入了 Rust 抽象，主要用于 Tyr 驱动，以便从 GPU 的 VA 空间分配内存用于内核 GPU 映射。它也可能用于 Rust Nova 驱动。该抽象强制使用内部自旋锁，不提供外部锁定，目前不支持仅使用 RCU 进行保护的加载。此版本整合了 Andrew Ballance 早期 RFC 的部分内容，并根据 Tyr 的用例进行了大量修改。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add AI coding assistant configuration to Linux kernel
- https://lore.kernel.org/all/20250725175358.1989323-1-sashal@kernel.org/
- 本次提交为 Linux 内核 添加了 AI 编码助手 的统一配置和文档。它为 Claude、GitHub Copilot 等工具提供通用设置，并规定了 AI 辅助开发的指导原则，包括：遵循内核编码标准、尊重开发流程、正确署名 AI 生成内容（通过 Co-developed-by 标签）以及理解许可要求，确保了 AI 参与的透明度和规范性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/damon: extend for page faults reporting based access monitoring
- https://lore.kernel.org/all/20250727201813.53858-1-sj@kernel.org/
- DAMON (Data Access MONitor) 扩展了其核心与操作集接口，以支持基于报告的内存访问监控，例如每 CPU 和只写访问监控。它通过 `damon_report_access()` 允许操作集主动报告访问信息，而不是被动查询。此外，引入了一个基于页错误的物理地址空间监控示例 (`paddr_fault`)，克服了传统页表访问位无法识别访问来源和类型的限制，可用于优化调度、虚拟机实时迁移和 NUMA 页面迁移等场景。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### virtio: Add support for Virtio message transport
- https://lore.kernel.org/all/cover.1753865268.git.viresh.kumar@linaro.org/
- 本 RFC 系列 引入了 Virtio 消息传输 (virtio-msg) 新类型，不同于传统的内存映射，它通过结构化消息进行传输，支持如邮箱、共享内存 FIFO 或 FFA 等机制。该系列包含核心传输支持，以及基于 ARM FF-A 和 回环设备 的两种消息传输总线实现，同时增强了保留内存子系统，以支持虚拟或动态发现设备的安全内存映射。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Live Update Orchestrator: PCI subsystem
- https://lore.kernel.org/all/20250728-luo-pci-v1-0-955b078dd653@kernel.org/
- 该 RFC 补丁系列为 Linux 内核 引入了 Live Update Orchestrator (LUO) PCI 子系统。它允许在不重启的情况下更新内核，通过注册 PCI 为 LUO 子系统并管理设备的热更新回调。它能处理 PCI 设备依赖（如 VF 依赖 PF、设备依赖 PCI 网桥），在 `kexec` 重启后恢复设备状态，包括 VF 数量。目标是实现 PCI 设备状态的无缝过渡。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Fair DRM scheduler
- https://lore.kernel.org/all/20250724141921.75583-1-tvrtko.ursulin@igalia.com
- 此 RFC 系列 提出了一种受 Linux CFS 启发的 DRM (Direct Rendering Manager) 公平调度算法。它旨在解决现有 FIFO 调度器中的 优先级饥饿问题，并简化代码。测试结果表明，新算法在 GPU 负载下能显著改善交互式客户端的调度公平性和性能，尤其在低优先级任务不会被完全“饿死”的情况下表现优异。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### unwind_user: Deferred unwinding infrastructure
- https://lore.kernel.org/all/20250725185512.673587297@kernel.org/
- 此补丁系列引入了 延迟展开（Deferred Unwinding）基础设施 到 Linux 内核，该功能将使用 SRCU 机制。此核心基础设施是许多其他相关补丁系列（如 x86、s390、perf、ftrace 和 sframe 工作）的基础，旨在通过提供一个通用的上游代码库，方便这些独立项目的并行开发。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Refcounted interrupts, SpinLockIrq for rust
- https://lore.kernel.org/all/20250717184055.2071216-1-lyude@redhat.com/
- 为 Rust 增加了控制本地处理器中断的绑定，支持在禁用本地处理器中断的情况下获取自旋锁，并在内核中通过引用计数实现本地中断控制。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Task local data
- https://lore.kernel.org/all/20250717164842.1848817-1-ameryhung@gmail.com/
- 引入了 “任务本地数据” 机制，允许用户空间进程高效地向 BPF 调度程序传递 “每任务提示”。它通过将用户页面直接固定到内核来实现，从而实现用户空间和 BPF 程序之间快速、低开销的数据共享，主要用于 sched_ext。
- 主线状态：✅ 已进入 mainline（约 v6.18-rc1；commit 引用了本系列 Link）

#### PM QoS: Add CPU affinity latency QoS support and resctrl integration
- https://lore.kernel.org/all/20250721124104.806120-1-quic_zhonhan@quicinc.com/
- 为 PM QoS 框架引入了基于 CPU 亲和性的延迟 QoS 支持。它允许将延迟约束应用于特定的 CPU 掩码，而非系统范围，旨在提高异构平台和嵌入式系统的电源效率。该系列还包括 resctrl 集成和相关文档更新。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### ext4: Add extsize support
- https://lore.kernel.org/all/cover.1753044253.git.ojaswin@linux.ibm.com/
- 为 ext4 文件系统引入了 extsize 支持。其主要目标是在不重新格式化文件系统为 bigalloc 的情况下，实现 ext4 的多块原子写入，并提供硬件加速和软件回退的灵活选择，以满足不同用户工作负载的需求。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### use per-vma locks for /proc/pid/maps reads
- https://lore.kernel.org/all/20250719182854.3166724-1-surenb@google.com/
- 优化 /proc/pid/maps 的读取效率，通过将原有的全局 mmap_lock 替换为每 VMA 锁，显著减少了与地址空间修改任务的锁竞争。这解决了优先级反转问题，提高了内存操作（如 mmap/munmap）的延迟表现，同时新增测试以确保数据一致性，即使在并发修改下也能处理 VMA 的合并与拆分。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Signed BPF programs
- https://lore.kernel.org/all/20250721211958.1881379-1-kpsingh@kernel.org/
- 引入了 BPF 程序签名支持，旨在提升安全性并允许非特权用户加载经过验证的 BPF 程序。核心思想是使用信任哈希链机制，通过签名 loader 程序及其元数据的哈希来确保完整性。它还增加了排他性 BPF 映射，防止未授权程序篡改数据，并更新了相关工具和自测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### perf auxtrace: Support AUX pause and resume with BPF
- https://lore.kernel.org/all/20250718-perf_aux_pause_resume_bpf_rebase-v2-0-992557b8fb16@arm.com/
- 扩展了 Perf 工具，通过 BPF 程序支持 AUX 跟踪的暂停和恢复，实现更细粒度的性能分析。它允许将 BPF 程序附加到各种追踪点（如 kprobe, uprobe），并通过新增的 bpf_perf_event_aux_pause 内核函数控制 AUX 数据的收集。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/mremap: permit mremap() move of multiple VMAs
- https://lore.kernel.org/all/cover.1752162066.git.lorenzo.stoakes@oracle.com/
- 此 v2 补丁系列共10个，旨在允许 `mremap()` 函数在指定 `MREMAP_FIXED` 标志时移动多个虚拟内存区域 (VMA)。这解决了当匿名映射因 VMA 碎片化而无法合并的问题，通过重构代码，将参数和 VMA 检查逻辑分组，并简化了 `uffd` 和 `mlock()` 的后处理，从而提升了 `mremap()` 的灵活性和效率。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc1；对应改动如「mm/mremap: permit mremap() move of multiple VMAs」）

#### erofs: support metadata compression
- https://lore.kernel.org/all/20250716173314.308744-1-hsiangkao@linux.alibaba.com/
- 此 v3 补丁系列为 EROFS 文件系统引入了**元数据压缩**功能，以减小镜像大小。它通过一个特殊的 "metabox" inode 收集并压缩所有 inode 元数据。用户可为元数据选择与数据压缩不同的算法（例如，元数据用 LZ4，数据用 LZMA）。初步测试显示，该功能可进一步缩小 Fedora 和 AOSP 镜像的体积。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### ext4: better scalability for ext4 block allocation
- https://lore.kernel.org/all/20250714130327.1830534-1-libaokun1@huawei.com/
- 此v3补丁系列共17个，旨在提高 **ext4 文件系统块分配**的可伸缩性，尤其是在多核服务器和容器场景下。通过优化组锁（group lock）和 `s_md_lock` 相关的代码，显著提升了 `fallocate` 等操作的性能（某些测试场景下性能提升超过14倍），并有效降低了文件碎片化。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc1；commit 引用了本系列 Link）

#### eea: Add basic driver framework for Alibaba Elastic Ethernet Adaptor
- https://lore.kernel.org/all/20250710112817.85741-1-xuanzhuo@linux.alibaba.com/
- eea：为阿里巴巴弹性以太网适配器（EEA）添加基础驱动框架，实现设备探测、初始化与基本收发路径，为后续功能扩展打基础。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### net/mlx5e: Add support for PCIe congestion events
- https://lore.kernel.org/all/1752130292-22249-1-git-send-email-tariqt@nvidia.com/
- 此补丁系列 (V2) 为 Mellanox mlx5e 网卡驱动增加了对 **PCIe 拥塞事件**的支持。固件在 PCIe 流量持续过高时会生成此类事件。系统通过 `ethtool` 计数器 (**pci_bw_in/outbound_high/low**) 暴露这些事件，并允许通过 `sysfs` 配置阈值，帮助用户判断 PCIe 带宽是否面临压力。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### reduce system memory requirement for hibernation
- https://lore.kernel.org/all/20250704101233.347506-1-guoqing.zhang@amd.com/
- 在配备大量VRAM（如8块192GB VRAM dGPU）的服务器上，现有机制会导致所有VRAM内容被复制到系统内存中，可能需要3TB内存，远超2TB系统内存，从而导致休眠失败。此修复通过在休眠前将GTT内存移动到共享内存并强制写入交换空间来释放这些内存。此外，它还优化了休眠恢复过程，避免了不必要的GPU恢复，从而显著减少了休眠时间（原观察到8块dGPU需要50分钟）。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### dm-pcache – persistent-memory cache for block devices
- https://lore.kernel.org/all/20250707065809.437589-1-dongsheng.yang@linux.dev/
- dm-pcache 是一个用于块设备的持久内存缓存。V2版本主要改进包括在持有自旋锁前进行请求分配、预分配缓存键和请求、使用`mempool_alloc`和`NOIO`，以及代码风格的调整。相较于RFC-V2，V1版本则更新了CRC算法、优化了缓存满时的重试机制、引入了新的pcache表格式等。此补丁共包含11个子补丁，涵盖了从内部头文件到缓存核心及目标初始化的各个方面。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### vmallloc and non-blocking GFPs
- https://lore.kernel.org/all/20250704152537.55724-1-urezki@gmail.com/
- 这个 RFC 系列补丁（共 7 个）旨在使vmalloc支持非阻塞的 GFP flags，例如GFP_ATOMIC或GFP_NOWAIT。目前仍是草案，存在硬编码的 GFP flags 等问题待解决。该系列已在non-block-alloc-test及CONFIG_DEBUG_ATOMIC_SLEEP=y环境下测试通过，并基于 Linux 内核 6.16-rc1 版本。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: Enable host userspace mapping for guest_memfd-backed memory for non-CoCo VMs
- https://lore.kernel.org/all/20250709105946.4009897-1-tabba@google.com/
- 这是一个KVM补丁系列旨在让非CoCo虚拟机支持**宿主用户空间映射**guest_memfd支持的内存。这对于简化VMM设计、通过移除直接映射增强安全性，以及为CoCo平台上的**受限mmap()支持**奠定基础至关重要。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc6；对应改动如「KVM: arm64: Enable support for guest_memfd backed memory」）

#### Support vector and more extended registers in perf
- https://lore.kernel.org/all/20250626195610.405379-1-kan.liang@linux.intel.com/
- 此补丁集为perf工具提供了**软件方案**，以支持在**溢出处理程序**中收集更多**扩展寄存器**（如YMM, ZMM, OPMASK, SSP, APX）。它利用**XSAVES指令**，不再局限于PEBS事件或特定平台。尽管硬件方案更优，但此方案在**Intel Ice Lake及更新平台**上启用，并引入新的`perf_event_attr`字段来配置SIMD寄存器。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Live Update Orchestrator
- https://lore.kernel.org/all/20250625231838.1897085-1-pasha.tatashin@soleen.com/
- Linux内核的Live Update Orchestrator (LUO) 子系统旨在实现**不停机内核热更新**，尤其适用于云部署。它基于KHO框架，提供**可编程控制**和**状态机管理**（NORMAL, PREPARED, FROZEN, UPDATED），支持**跨kexec边界保存元数据**、**文件描述符**及**子系统状态**，并通过ioctl和sysfs提供用户空间接口。
- 主线状态：✅ 已进入 mainline（约 v6.19-rc1；对应改动如「liveupdate: luo_core: Live Update Orchestrator」）

#### rust: DebugFS Bindings
- https://lore.kernel.org/all/20250627-debugfs-rust-v8-0-c6526e413d40@google.com/
- 为内核 debugfs 提供 Rust 绑定/抽象，让 Rust 驱动能安全地创建、读写与管理 debugfs 目录与文件。
- 主线状态：✅ 已进入 mainline（；对应改动如「rust: debugfs: remove unsafe blocks from traits impl for」）

#### Squashfs: add page cache share support
- https://lore.kernel.org/all/20250626003644.3675-1-liubo03@inspur.com/
- 此补丁为 **Squashfs 文件系统**引入了**页面缓存共享**功能，旨在解决容器场景下相同文件重复占用内存的问题。通过为文件设置 **MD5 值扩展属性**，系统能够识别并共享相同文件的页面缓存。测试显示，启用该功能可显著**减少页面缓存占用**，例如将501MiB的缓存减少到1052MiB。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: x86: Provide a cap to disable APERF/MPERF read intercepts
- https://lore.kernel.org/kvm/20250626001225.744268-1-seanjc@google.com/
- 此KVM补丁系列引入了**x86功能**，允许**禁用对IA32_APERF和IA32_MPERF寄存器读取的截获**。这使得客户机能够直接读取这些MSR，以确定物理LPU的有效频率倍频。虽然不完全等同于完整的CPUID支持，但在受限虚拟化环境中（如vCPU绑定、无TSC倍频、无休眠/恢复），此功能可满足特定需求。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc1；commit 引用了本系列 Link）

## 2025年 第06期 (Start From 2025/06/01)

#### New perf ilist app
- https://lore.kernel.org/all/20250616051500.1047173-1-irogers@google.com/
- 这是一系列共15个补丁，旨在为perf工具引入一个基于 Python 和 Textual 的新 ilist 应用程序。该应用能展示perf的PMU和事件，显示事件信息（类似 perf list），并在底部显示事件的总量和CPU活动情况。补丁还包括对perf和perf python C API的修复，特别是支持Python读取工具PMU计数器。此外，它改进了软件PMU和tracepoint PMU对事件迭代的支持，并移除了软件PMU的旧有硬编码解析方式。最终的补丁新增了 ilist 命令。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### BIG TCP for UDP tunnels
- https://lore.kernel.org/all/20250617144017.82931-1-maxim@isovalent.com/
- Maxim Mikityanskiy提交的这个补丁系列旨在使 BIG TCP 支持 UDP 隧道。它分为两部分：首先，移除 BIG TCP IPv6 中不必要的逐跳（Hop-by-Hop, HBH）扩展头，因为HBH头在封装场景下存在性能和处理问题。其次，修复阻碍 BIG TCP 与 VXLAN 和 GENEVE 隧道协同工作的代码，主要是解决 skb->len 大于64KB时长度截断的问题。移除HBH头能简化实现，并使其与BIG TCP IPv4保持一致。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Cache coherency management subsystem
- https://lore.kernel.org/all/20250624154805.66985-1-Jonathan.Cameron@huawei.com/
- 这个补丁系列v2提出了一个通用的缓存一致性管理子系统，旨在支持CPU外部设备对特定物理地址范围进行缓存回写和失效操作，解决传统CPU指令（如x86的WBINVD）无法有效处理外部内存变化（如CXL热插拔内存）的问题。它简化了RFC版本的设计，移除了设备类概念，采用简单的注册列表，并通用化了对ARM64的支持。该系列还新增了 cpu_cache_invalidate_memregion() 接口，并包含了HiSilicon HHA和ACPI示例实现，以验证其可行性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/damon: allow DAMOS auto-tuned for per-memcg per-node memory usage
- https://lore.kernel.org/all/20250619220023.24023-1-sj@kernel.org/
- 该 RFC 补丁系列为 DAMON 的 DAMOS 自动调优功能引入了两个新的目标度量：基于 cgroup 和 NUMA 节点的内存使用量（已用和空闲百分比）。这使得 DAMOS 能针对多租户系统中的内存分层等 cgroup 感知场景进行细粒度内存管理。用户现在可以为每个 cgroup 在特定 NUMA 节点上设定内存使用目标（如百分比），DAMOS 将自动调整操作（如热页迁移、冷页回收）的激进程度，以实现这些目标，从而提高公平性和资源利用率。
- 主线状态：✅ 已进入 mainline（约 v6.19-rc1；对应改动如「mm/damon: add DAMOS quota goal type for per-memcg per-no」）

#### mm: introduce snapshot_page()
- https://lore.kernel.org/all/cover.1750170418.git.luizcap@redhat.com/
- 该RFC补丁系列引入了一个名为 snapshot_page() 的辅助函数，用于创建 struct page 及其关联 struct folio 的一致性快照。此函数旨在帮助调用者获得页框的稳定视图，避免在 folio 分裂等过程中遇到部分更新或不一致的状态，从而减少潜在的崩溃和BUG。该系列还展示了 kpagecount 和 stable_page_flags() 如何使用此新函数。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Kernel API specification framework
- https://lore.kernel.org/all/20250624180742.5795-1-sashal@kernel.org/
- 这个RFC v2补丁系列提出了一个内核 API 规范框架，旨在解决用户空间API兼容性难以检测的问题。它通过在内核代码中直接定义 API 规格的机器可读格式，实现运行时验证、文档生成、工具集成和自动化 API 破坏检测。新版本扩展了对  sysfs 属性和 socket () 系统调用的支持，以期提供更可靠的API契约验证，确保Linux内核的向后兼容性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched/numa, mm/numa: Soft Affinity via numa_preferred_nid
- https://lore.kernel.org/all/20250622191622.3296825-1-chris.hyser@oracle.com/
- 这个v3补丁系列（共2个）旨在通过 numa_preferred_nid 实现软亲和性（Soft Affinity）。它允许有经验的用户或 NUMA 感知的应用程序为任务设置首选 NUMA 节点，以指导自动NUMA平衡行为。这对于内存固定（如RDMA缓冲区）等场景特别有用。与之前被拒绝的实现不同，此方案不修改调度器行为，而是利用现有NUMA平衡机制，主要通过 prctl() 设置/获取 numa_preferred_nid 值。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### cpuset/isolation: Honour kthreads preferred affinity
- https://lore.kernel.org/all/20250620152308.27492-1-frederic@kernel.org/
- 此系列补丁（共27个）旨在解决 cpuset 在创建、删除或更新隔离分区时，覆盖未绑定 kthread 首选亲和性的问题。核心思想是将kthread的亲和性更新从cpuset转移到kthread相关的代码中，由housekeeping机制统一分派新的CPU掩码，从而确保 kthread 的首选亲和性（节点或自定义 cpumask）得到遵守。此举也是未来使 nohz_full= 通过cpuset可变的重要一步。
- 主线状态：✅ 已进入 mainline（约 v7.0-rc1；对应改动如「kthread: Honour kthreads preferred affinity after cpuset」）

#### BPF indirect jumps
- https://lore.kernel.org/all/20250615085943.3871208-1-a.s.protopopov@gmail.com/
- 该RFC补丁系列（共9个）为BPF引入间接跳转支持，主要针对x86架构。它实现了一种新的BPF_MAP_TYPE_INSN_SET 映射类型来跟踪指令映射，并基于此实现了间接跳转功能。此外，该系列还增加了对  LLVM 编译的含间接跳转程序的支持。由于需要自定义LLVM且测试尚不完善，目前仍为RFC阶段，但现有自测试已通过。
- 主线状态：✅ 已进入 mainline（约 v6.19-rc1；commit 引用了本系列 Link）

#### Hierarchical Constant Bandwidth Server
- https://lore.kernel.org/all/20250605071412.139240-1-yurand2000@gmail.com/
- 此RFC补丁系列（共9个）实现了分层恒定带宽服务器（HCBS），旨在取代Linux内核中现有的 RT_GROUP_SCHED，提供更健壮的实时调度机制。HCBS允许为运行 SCHED_FIFO/SCHED_RR 任务的cgroup预留带宽，支持cgroup v2，并通过为每个CPU分配本地运行队列和 dl_servers 来管理调度。该补丁集主要包括准备工作、HCBS基础实现、移除旧代码以及对cgroup的支持。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: guest_memfd: Support in-place conversion for CoCo VMs
- https://lore.kernel.org/all/20250613005400.3694904-1-michael.roth@amd.com/
- 这项**RFC v1补丁集**旨在让CoCo 虚拟机支持**guest_memfd内存的就地转换**，允许私有和共享页面使用相同的物理内存。它解决了当前依赖“打洞”释放内存的缺点，如对1GB HugeTLB支持的限制和PCI直通场景下的内存翻倍问题。该系列旨在为SEV-SNP、TDX和pKVM等平台提供通用的就地转换支持。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### io_uring cmd for tx timestamps
- https://lore.kernel.org/all/cover.1749657325.git.asml.silence@gmail.com/
- 这份v3补丁集为`io_uring`引入了一个**新的socket命令**，用于获取**发送时间戳**。它通过内部轮询socket的`POLLERR`并将时间戳到达时发布出来，重用了现有的时间戳基础设施并从socket的错误队列中获取。v3版本增加了区分软件/硬件时间戳的标志，并在CQE中以位标志体现。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### veristat: memory accounting for bpf programs
- https://lore.kernel.org/all/20250613072147.3938139-1-eddyz87@gmail.com/
- 这份v3补丁集旨在为BPF程序添加**内存消耗统计**功能，修改`veristat`工具以显示峰值内存使用（MiB）和状态数。它通过在`veristat`执行前进入新的cgroup来测量`bpf_object__load()`前后的`memory.peak`差异。更新包括将verifier内存分配切换到`GFP_KERNEL_ACCOUNT`，并改进了cgroup处理和错误报告。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc1；commit 引用了本系列 Link）

#### Add TDX intra-host migration support
- https://lore.kernel.org/all/cover.1749672978.git.afranji@google.com/
- 这是一系列关于**TDX（可信域扩展）主机内迁移**的补丁的**RFC v2**版本，它基于最新的kvm/next (v6.16-rc1) 并解决了v1中的注释。主要更新包括：防止死锁警告、允许为未初始化VM创建vCPU、优化核心逻辑、处理迁移期间注入的已发布中断，并增加了自测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### [PATCH 00/13] Parallelizing filesystem writeback
- https://lore.kernel.org/all/20250529111504.89912-1-kundan.kumar@samsung.com/
- 该补丁通过为每个后端设备（BDI）引入多个回写上下文来并行化文件系统回写，每个上下文独立运行。此举显著提高了 PMEM 和 NVMe 设备的 IOPS 和吞吐量，同时没有增加文件系统碎片。为避免碎片化，inode 现在被绑定到特定的回写上下文。未来版本将允许用户配置回写上下文数量。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### TDX: Enable Dynamic PAMT
- https://lore.kernel.org/all/20250609191340.2051741-1-kirill.shutemov@linux.intel.com/
- 此补丁集在 TDX 中引入了动态 PAMT (Physical Address Metadata Table)。之前 PAMT 静态分配占用约 0.4% 系统内存，现在通过 动态分配 4K 级别 PAMT，将静态分配减少至 0.004%。PAMT 内存随 TDX 保护页面的增删而动态分配和回收，显著降低了内存占用，并已通过 SEAMCALLs 进行管理。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### BPF controlled io_uring
- https://lore.kernel.org/all/cover.1749214572.git.asml.silence@gmail.com/
- 该 RFC v2 补丁系列为 io_uring 引入了 BPF struct_ops 支持。这意味着 BPF 程序可以直接在内核中处理 io_uring 事件和提交请求，无需返回用户空间。初步测试显示，相比传统 io_uring， BPF 版本可提速高达 80%。这允许请求间更灵活的关联，并能访问内核资源，未来还将扩展更多回调。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### LKMM generic atomics in Rust
- https://lore.kernel.org/all/20250609224615.27061-1-boqun.feng@gmail.com/
- 此为 LKMM Rust 原子操作的 v4 补丁集，旨在为 Rust 在 Linux 内核中提供与 LKMM 兼容的原子类型。该系列补丁实现了对整数和指针的原子加载、存储、交换、比较交换和算术操作，并支持内存屏障。作者希望尽快合入，以支持日益增长的 Rust 原子操作使用。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add multiple address spaces support to VDUSE
- https://lore.kernel.org/all/20250606115012.1331551-1-eperezma@redhat.com/
- 该RFC补丁系列为 VDUSE 设备添加了多地址空间支持。其核心思想是使用  ASID (地址空间标识符) 来隔离不同的内存映射，特别是针对控制 virtqueue。这允许用户空间 VMM (QEMU) 影子化控制 virtqueue，从而实现正确的设备状态管理（如实时迁移），并防止 Guest 直接访问。该功能已在 vhost_vdpa 上测试。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### fuse: use iomap for buffered writes + writeback
- https://lore.kernel.org/all/20250606233803.1421259-1-joannelkoong@gmail.com/
- 该系列补丁为 FUSE 文件系统引入了  iomap 支持，用于缓冲写入和回写脏页。此举旨在配合大页功能，实现更精细的脏数据追踪，避免在少量数据脏时回写整个大页。为此，新增了不依赖块设备的  IOMAP_IN_MEM 类型。测试显示，这能显著提升部分场景的写入性能。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc6；对应改动如「fuse: use iomap for buffered writes」）

#### alloc_tag: add per-NUMA node stats
- https://lore.kernel.org/all/20250610233053.973796-1-cachen@purestorage.com/
- 这个补丁为 /proc/allocinfo 增加了 per-NUMA 节点内存分配统计。现在，每个 alloc_tag 不再是单一聚合计数器，而是可以跟踪每个 NUMA 节点的独立字节和调用计数。这通过新的 CONFIG_MEM_ALLOC_PROFILING_PER_NUMA_STATS 选项控制，提供了更细粒度的内存分配分析。为减少内存开销，计数器是动态分配的。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Enable huge-vmalloc permission change
- https://lore.kernel.org/all/20250530090407.19237-1-dev.jain@arm.com/
- 该补丁集旨在为 arm64 架构默认启用 vmalloc 空间的巨页映射。目前__change_memory_common() 无法处理巨页权限修改，因此该系列改用 walk_page_range_novma() 来支持此功能。这与 Yang Shi 的线性映射巨页工作相关联，特别是在支持 BBML2（可无 “先破坏再创建” 地拆分线性映射）的系统上，将允许对巨页进行权限修改。即使不依赖 Yang 的工作，此补丁也为多种内核映射（如线性映射和 vmalloc）提供了启用巨页权限修改的机制。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### ARM64 PMU Partitioning
- https://lore.kernel.org/all/20250602192702.2125115-1-coltonlewis@google.com/
- 该补丁系列为ARM64引入了分区 PMU 方案，允许KVM将性能监控单元计数器划分为宿主机和虚拟机专用。这使得虚拟机能直接访问其保留的计数器， 显著降低了 perf 工具在虚拟机中使用的开销，减少了陷入宿主机内核的次数。性能测试显示，与现有模拟PMU相比，分区PMU在运行时、系统时间和基准分数上都有显著提升。虽然增加了上下文切换时的寄存器开销，但未来版本可能通过惰性切换来优化。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### coredump: allow for flexible coredump handling
- https://lore.kernel.org/all/20250530-work-coredump-socket-protocol-v1-0-20bde1cd4faa@kernel.org/
- 该补丁系列通过扩展coredump socket，赋予用户空间 coredump 服务器对单个 coredump 请求的灵活处理能力。服务器可决定由内核写入coredump、自行生成，或直接拒绝。内核发送 coredump_req 告知请求信息和支持的功能，服务器回复 coredump_ack 选择所需功能。这实现了更精细的coredump管理，并支持新旧内核协议的兼容性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### timers: Exclude isolated cpus from timer migation
- https://lore.kernel.org/all/20250530142031.215594-1-gmonaco@redhat.com/
- 该补丁旨在防止定时器迁移到隔离 CPU，以避免高负载隔离核上的性能下降和延迟尖峰。在128核机器上，该优化将最大延迟从1203微秒降至10微秒。它通过将隔离CPU视为“不可用”来排除其定时器迁移，同时确保非隔离CPU能处理全局定时器。
- 主线状态：✅ 已进入 mainline（约 v6.19-rc1；对应改动如「timers/migration: Exclude isolated cpus from hierarchy」）

#### Add a deadline server for sched_ext tasks
- https://lore.kernel.org/all/20250602180110.816225-1-joelagnelf@nvidia.com/
- 该补丁系列为 sched_ext 任务引入了 deadline server，以解决其被实时（RT）任务饿死的问题。由于RT节流机制被deadline server取代以仅提升CFS任务，sched_ext 任务常受影响。此改动旨在通过提升 sched_ext 任务优先级，确保其免受饿死。系列包含相关内核修改和selftest，以验证问题修复。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched/fair: Reorder scheduling related structs to reduce cache misses
- https://lore.kernel.org/all/20250602180544.3626909-1-zecheng@google.com/
- 该补丁通过重新组织 struct cfs_rq 和 struct sched_entity 的字段，提升了 CPU 缓存局部性。此优化显著减少了共享缓存（LLC）的缺失（Intel 和 AMD 平台分别降低约 17-22%），尤其在多核服务器和大量 cgroup 场景下，改进了 CFS 调度性能，例如 tg_throttle_down 等函数。虽然对应用吞吐量影响不明显，但降低了内核开销，对于大规模 cgroup 环境的服务器负载有益。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rust: add initial scatterlist abstraction
- https://lore.kernel.org/all/20250528221525.1705117-1-abdiel.janulgue@gmail.com/
- 该补丁集为Rust引入了 scatterlist 抽象的初始实现，其核心在于使用  typestate 模式。这解决了之前scatterlist API的限制，通过引入两种迭代器（构建列表和DMA映射后）和更清晰的状态转换，强制限制了在特定状态下不允许的函数调用（如在未DMA映射时查询DMA地址）。这将提升Rust中处理DMA scatterlist的安全性与正确性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Implement dmabuf direct I/O via copy_file_range
- https://lore.kernel.org/all/20250603095245.17478-1-tao.wangtao@honor.com/
- 该补丁通过实现 dmabuf 的 copy_file_range 直接 I/O 来优化文件数据加载。由于现有 mmap 缺乏直接I/O，导致AI模型等大型文件加载延迟。此方案允许跨文件系统（FS）复制到内存文件，并通过为 dmabuf 添加 copy_file_range 回调，实现磁盘到 dmabuf 的零拷贝。测试显示，相比传统缓冲I/O，性能提升高达260%，显著降低CPU开销。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Host side (KVM/VFIO/IOMMUFD) support for TDISP using TSM
- https://lore.kernel.org/all/20250529053513.1592088-1-yilun.xu@linux.intel.com/
- 该补丁系列为使用TSM的TDISP提供宿主机端（KVM/VFIO/IOMMUFD）支持，涵盖私有设备分配的整个生命周期。它基于Dan的Core TSM基础设施系列，并整合了社区中现有的WIP补丁集。该系列分为三个部分：KVM MMU中的私有MMIO映射、VFIO & IOMMUFD中的TSM绑定/解绑/Guest请求管理，以及TDX特定序列强制执行。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2025年 第05期 (Start From 2025/05/01)

#### virtio-net: support zerocopy multi buffer XDP in mergeable
- https://lore.kernel.org/all/20250527161904.75259-1-minhquangbui99@gmail.com/
- 此 RFC 补丁通过利用带分片的 XDP 缓冲区，使 virtio-net 支持多缓冲区零拷贝 XDP，以处理 MTU 设置为 9000 时可能超过单个 XDP 缓冲区的数据包。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### net/mlx5e: Add support for devmem and io_uring TCP zero-copy
- https://lore.kernel.org/all/1747950086-1246773-1-git-send-email-tariqt@nvidia.com/
- 该系列补丁为ConnectX7及以上网卡增加了 devmem 和 io_uring 的 TCP 接收零拷贝支持，并通过开启  HW-GRO 提升性能。测试显示，io_uring模式下吞吐量显著提升，MTU 9000时可达187 Gbps。此更新引入了netmem API、SHAMPO代码清理、独立的报头页池以及ethool统计，并实现了队列管理操作和tcp-data-split参数暴露。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### x86/resctrl: Support L3 Smart Data Cache Injection Allocation Enforcement (SDCIAE)
- https://lore.kernel.org/all/cover.1747943499.git.babu.moger@amd.com/
- 此补丁系列为 x86/resctrl 框架引入了对 L3 智能数据缓存注入分配强制 (SDCIAE) 的支持，在 resctrl 子系统中称为 "io_alloc"。SDCIAE 是AMD即将推出的硬件特性，允许系统软件控制L3缓存中用于直接I/O设备数据注入的部分，以减少DRAM带宽需求并降低延迟。该功能通过 /sys/fs/resctrl/info/L3/io_alloc 和 /sys/fs/resctrl/info/L3/io_alloc_cbm 接口进行配置和管理，并需Linux内核支持TLP处理提示 (TPH)。
- 主线状态：✅ 已进入 mainline（约 v6.19-rc4；对应改动如「x86/cpufeatures: Add support for L3 Smart Data Cache Inj」）

#### bpf: tcp: Exactly-once socket iteration
- https://lore.kernel.org/all/20250520145059.1773738-1-jordan@jrife.io/
- 改进 BPF 的 TCP/socket 迭代器，保证遍历套接字时每个 socket 恰好被访问一次，避免重复或遗漏。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm/mempolicy: Weighted Interleave Auto-tuning
- https://lore.kernel.org/all/20250520141236.2987309-1-joshua.hahnjy@gmail.com/
- 该补丁为内存节点加权交错（weighted interleave）引入自动调优模式：根据系统报告的带宽数据动态计算默认权重，并响应热插拔事件；同时保留手动模式，并设定无效写入返回错误。优点在于开箱即可获得合适权重，提升多节点带宽利用率，自动适配硬件变化。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc1；commit 引用了本系列 Link）

#### Allow mmap of /sys/kernel/btf/vmlinux
- https://lore.kernel.org/all/20250510-vmlinux-mmap-v4-0-69e424b2a672@isovalent.com/
- 该补丁在 /sys/kernel/btf/vmlinux 上新增只读 mmap 支持，采用 remap_pfn_range 映射内核 BTF 数据至用户态，避免复制开销（约 75% 内存节省），并完善权限与错误检测，可显著提升 eBPF 工具库解析效率与内存利用率。
- 主线状态：✅ 已进入 mainline（commit 引用了本系列 Link）

#### memcg: make memcg stats irq safe
- https://lore.kernel.org/all/20250513031316.2147548-1-shakeel.butt@linux.dev/
- 此补丁将 memcg 统计更新相关的本地 IRQ 禁用移至调用侧，删除冗余的 local_irq_save/restore，并在统计更新中新增 NMI 上下文安全检查，简化对象缓存并发锁逻辑；可降低中断上下文开销，提高内存 cgroup 统计更新效率与可靠性
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### memcg: nmi-safe kmem charging
- https://lore.kernel.org/all/20250509232859.657525-1-shakeel.butt@linux.dev/
- 此系列补丁将 memcg 统计更新改为 IRQ 安全，支持在 task/softirq/hardirq 上下文无需禁中断即可更新统计；重构原子操作与锁策略（如将 preempt-disable 移至调用侧、objcg stock trylock 无中断禁用），并移除冗余锁，简化并发逻辑，可降低中断上下文开销，提升内存 cgroup 统计的效率与可靠性。
- 主线状态：✅ 已进入 mainline（约 v6.16-rc1；对应改动如「memcg: disable kmem charging in nmi for unsupported arch」）

#### rust: add support for Port io
- https://lore.kernel.org/all/20250509031524.2604087-1-andrewjballance@gmail.com/
- 此系列补丁为 Rust for Linux 内核框架引入对端口 I/O（PIO）的支持：将原有 Io 类型拆分为可同时访问 PIO/MMIO 的通用 Io 与仅用于 MMIO 的 MMIo，并将 pci::Bar 设计为对 Io 泛化，允许在编译期指定 I/O 类型。优势在于在 Rust 编写的 PCI 驱动中，既能安全地处理 PIO，又可针对 MMIO 进行性能优化，提升驱动灵活性与效率。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kexec: Enable CMA based contiguous allocation
- https://lore.kernel.org/all/20250512225752.11687-1-graf@amazon.com/
- 该补丁为 kexec_file 引导器新增基于 CMA 的物理连续内存分配：优先从 CMA 获取目标映像空间，省去热阶段内存拷贝；同时保留禁用选项并检测重叠。可显著加快 kexec 启动速度，提升在 DMA 硬件冲突场景下的可靠性。
- 主线状态：✅ 已进入 mainline（约 v6.19-rc4；对应改动如「kexec: enable CMA based contiguous allocation」）

#### sched/fair: introduce new scheduler group type group_parked
- https://lore.kernel.org/all/20250512115325.30022-1-huschle@linux.ibm.com/
- 该补丁在实时调度中引入对 “已停用（parked）”CPU 的感知：在 rt_task_fits_capacity 中新增 arch_cpu_parked 检查，并在 find_lowest_rq 中跳过这些 CPU，动态将 RT 任务迁移到可用核上。优势是避免将实时任务调度到无效 CPU，提升实时性能和负载均衡的准确性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched/numa: add statistics of numa balance task migration
- https://lore.kernel.org/all/cover.1746611892.git.yu.c.chen@intel.com/
- 该补丁集在 /sys/fs/cgroup/.../memory.stat、/proc/[PID]/sched 及 /proc/vmstat 中新增 NUMA 平衡任务迁移与交换统计，并在选择交换目标时跳过内核线程以避免 NULL mm_struct 异常。可快速评估负载迁移效果，提升 NUMA 调度的可观测性与稳定性。
- 主线状态：⚠️ 曾合入后被回退（revert），当前未在主线

#### zswap compression batching
- https://lore.kernel.org/all/20250430205305.22844-1-kanchana.p.sridhar@intel.com/
- 该补丁基于 ahash 请求链框架，为 crypto_acomp 增加同步 / 异步请求链 API：可将多条压缩 / 解压请求串联或并发提交至 Intel IAA 硬件，实现批量并行处理，显著降低延迟并提升吞吐；同时复用通用链框架，便于驱动集成与维护。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Consolidate iommu page table implementations (AMD)
- https://lore.kernel.org/all/0-v2-5c26bde5c22d+58b-iommu_pt_jgg@nvidia.com/
- 该补丁集首步将各 IOMMU 页表格式的映射 / 拆映射等算法从驱动中抽离集中到 io-pgtable 框架，消除重复实现，统一 API，并以 AMD 硬件为首例保持行为兼容。创新在于减少代码冗余，便于集中测试与优化，为后续批量映射、动态拆页、内存回收等高级特性铺路，提升可维护性与性能扩展能力。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### coredump: add coredump socket
- https://lore.kernel.org/all/20250505-work-coredump-socket-v3-0-e1832f0e1eae@kernel.org/
- 该补丁为 coredump 增加第 (3) 种模式：通过在 core_pattern 中以 @linuxafsk/coredump_socket 指定抽象 AF_UNIX socket，内核在初始网络命名空间创建固定地址 linuxafsk/coredump.socket，崩溃时任务无需再 spawn helper 进程，只需 connect 该 socket 即可传输转储数据。优势在于减少特权 helper 的生成与权限复杂度，降低锁竞争和进程创建开销，并可更好地与容器隔离和网络命名空间集成
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### x86: Add support for NMI-source reporting with FRED
- https://lore.kernel.org/all/20250507012145.2998143-1-sohil.mehta@intel.com/
- 此补丁系列在 x86 架构中引入 Intel FRED（Flexible Return and Event Delivery）机制的 NMI 源报告功能：通过 16 位位图标识多个 NMI 来源，扩展注册接口并在 APIC 层对 NMI 进行编码和处理。替代了遍历全量回调的方式，实现按位图精准调度，同时增加调试信息打印。优势在于大幅降低 NMI 处理开销、提升处理精度和故障诊断能力，并为 Perf/KVM 等集成场景提供底层支持。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### x86: Introduce centralized CPUID model
- https://lore.kernel.org/all/20250506050437.10264-1-darwi@linutronix.de/
- 引入集中式 CPUID 模型，统一 x86 对 CPUID 特性的解析与呈现，替代散落各处的直接 CPUID 读取。
- 主线状态：✅ 已进入 mainline（约 v7.2-rc1；对应改动如「x86/cpuid: Introduce a centralized CPUID parser」）

#### Intel RAR TLB invalidation
- https://lore.kernel.org/all/20250506003811.92405-1-riel@surriel.com/
- 该 RFC 补丁系列引入 Intel “Remote Action Request”（RAR） 硬件特性检测与支持，将 TLB 失效通知从发送 IPIs 转为由 RAR 位图触发内核自发射，减少跨核中断开销，显著提升大规模多核系统的页表失效延迟与可扩展性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### KVM: TDX huge page support for private memory
- https://lore.kernel.org/all/20250424030033.32635-1-yan.y.zhao@intel.com/
- 该补丁在 KVM/TDX 的 private_max_mapping_level 钩子中新增 prefetch 参数，将预取故障的最大映射级别强制为 4KB，避免在 fault 路径中直接生成 2MB 巨页而导致分割失败；借助更完善的 SEAMCALL 拆页处理，提升了页表 fault 的稳定性和性能扩展能力。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### perf: Deferred unwinding of user space stack traces
- https://lore.kernel.org/all/20250424162529.686762589@goodmis.org/
- 该 v5 系列补丁为 perf 引入用户态栈跟踪的延迟展开机制：通过新增架构无关的 unwind_user 通用 API、帧指针与兼容模式支持、deferred cache 缓存及 perf record/script 工具链扩展，实现先采样后异步展开的调用链，降低在线解算开销、提升高并发场景下的性能与跟踪深度，同时便于跨架构维护。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### nommu UML
- https://lore.kernel.org/all/cover.1745980082.git.thehajime@gmail.com/
- 让 User-Mode Linux（UML）支持 NOMMU（无 MMU）模式运行，用于无 MMU 场景的测试与验证。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm: BPF OOM
- https://lore.kernel.org/bpf/20250428033617.3797686-1-roman.gushchin@linux.dev/
- 允许用 BPF 程序自定义 OOM 处理：内存耗尽时由 BPF 决定回收或挑选牺牲进程等策略。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### mm, bpf: BPF based THP adjustment
- https://lore.kernel.org/bpf/20250429024139.34365-1-laoar.shao@gmail.com/
- 用 BPF 动态调整透明大页（THP）策略，按工作负载决定为哪些区域、何时启用大页。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

## 2025年 第04期 (Start From 2025/04/01)

#### ip: improve tcp sock multipath routing
- https://lore.kernel.org/all/20250420180537.2973960-1-willemdebruijn.kernel@gmail.com/
- 改进 TCP 套接字的多路径路由选择逻辑，提升多路径/多出口场景下的路由决策与连接性能。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### introduce kmemdump
- https://lore.kernel.org/all/20250422113156.575971-1-eugen.hristev@linaro.org/
- 引入 kmemdump 机制，选择性导出指定内核内存区域，用于调试与崩溃现场分析。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### bpf: Fast-Path approach for BPF program Termination
- https://lore.kernel.org/all/20250420105524.2115690-1-rjsu26@gmail.com/
- 为 BPF 程序终止引入快速路径，更高效、安全地中止长时间运行或异常的 BPF 程序。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched_ext: Introduce rq lock tracking
- https://lore.kernel.org/all/20250419123536.154469-1-arighi@nvidia.com/
- 为 sched_ext 增加运行队列（rq）锁跟踪，让 BPF 调度器正确感知 rq 锁状态，避免死锁与竞态。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched: Introduce Cache aware scheduling
- https://lore.kernel.org/lkml/cover.1745199017.git.yu.c.chen@intel.com/
- 引入缓存感知调度，尽量把相关任务聚拢到共享 LLC 的 CPU 上运行，减少跨缓存迁移开销。
- 主线状态：✅ 已进入 mainline（；对应改动如「sched/topology: Provide arch_llc_mask for cache aware sc」）

#### Eliminate Dying Memory Cgroup
- https://lore.kernel.org/all/20250415024532.26632-1-songmuchun@bytedance.com/
- 解决离线（濒死）memcg 因残留引用长期滞留的问题，及时回收以降低内存与统计开销。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「mm: memcontrol: eliminate dying memory cgroup」）

#### pcache: Persistent Memory Cache for Block Devices
- https://lore.kernel.org/all/20250414014505.20477-1-dongsheng.yang@linux.dev/
- pcache：用持久内存作为块设备缓存层，加速块 I/O 并在掉电后保持缓存数据（dm-pcache）。
- 主线状态：✅ 已进入 mainline（；对应改动如「dm-pcache: remove unused 'cache' parameter from cache_ke」）

#### Ext4 Fast Commit Performance Patchset
- https://lore.kernel.org/all/20250414165416.1404856-1-harshadshirwadkar@gmail.com/
- 优化 ext4 fast commit 的性能与可扩展性，降低提交开销、提升 fsync 密集负载吞吐。
- 主线状态：✅ 已进入 mainline（；对应改动如「ext4: improve fast_commit performance and scalability
」）

#### BPF Standard Streams
- https://lore.kernel.org/all/20250414161443.1146103-1-memxor@gmail.com/
- 为 BPF 引入标准流（类 stdout/stderr）机制，统一 BPF 程序的输出与日志通道。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc1；对应改动如「bpf: Introduce BPF standard streams」）

#### Single RunQueue Proxy Execution (v16)
- https://lore.kernel.org/all/20250412060258.3844594-1-jstultz@google.com/
- 单运行队列的代理执行（proxy-exec）：实现优先级继承，避免持锁低优任务阻塞高优任务。
- 主线状态：✅ 已进入 mainline（；对应改动如「locking: mutex: Fix proxy-exec potentially deactivating 」）

#### Restrict devmem for confidential VMs
- https://lore.kernel.org/all/174433453526.924142.15494575917593543330.stgit@dwillia2-xfh.jf.intel.com/
- 在机密虚拟机场景下限制 devmem（/dev/mem 等）访问，收紧设备内存暴露面以保护客户机机密性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rust: add support for maple trees
- https://lore.kernel.org/all/20250405060154.1550858-1-andrewjballance@gmail.com/
- 为 Rust 提供 maple tree（区间树）抽象绑定，供 Rust 内核代码安全使用该数据结构。
- 主线状态：✅ 已进入 mainline（；对应改动如「rust: maple_tree: add __rust_helper to helpers
」）

#### KVM: iommu: Overhaul device posted IRQs support
- https://lore.kernel.org/all/20250404193923.1413163-1-seanjc@google.com/
- 重构 KVM 设备投递中断（posted IRQ）支持，统一并简化 IOMMU/VMX 投递中断处理路径。
- 主线状态：✅ 已进入 mainline（；对应改动如「KVM: VMX: Don't register posted interrupt wakeup handler」）

#### Rust support for mm_struct, vm_area_struct, and mmap
- https://lore.kernel.org/all/20250408-vma-v16-0-d8b446e885d9@google.com/
- 为 mm_struct、vm_area_struct 与 mmap 提供 Rust 抽象，让 Rust 代码安全操作进程地址空间。
- 主线状态：✅ 已进入 mainline（约 v6.16-rc1；对应改动如「mm: rust: add abstraction for struct mm_struct」）

#### cgroup: separate rstat trees
- https://lore.kernel.org/all/20250404011050.121777-1-inwardvessel@gmail.com/
- 让各 cgroup 子系统使用独立的 rstat 统计树，降低锁竞争、提升统计更新的可扩展性。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc3；对应改动如「cgroup: use separate rstat trees for each subsystem」）

#### bpf: Introduce modular verifier
- https://lore.kernel.org/bpf/cover.1744169424.git.dxu@dxuuu.xyz/
- 将 BPF 校验器模块化重构，提升可维护性并便于扩展新的校验逻辑与特性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Support auto counter reload
- https://lore.kernel.org/all/20250327195217.2683619-1-kan.liang@linux.intel.com/
- 支持 PMU 计数器自动重载（auto counter reload），减少采样中断中软件重置计数器的开销。
- 主线状态：✅ 已进入 mainline（；对应改动如「perf tests: Add auto counter reload (ACR) sampling test
」）

#### MSR refactor with new MSR instructions support
- https://lore.kernel.org/all/20250331082251.3171276-1-xin@zytor.com/
- 重构 MSR 访问并支持新的 MSR 指令（immediate form），提升访问效率与代码清晰度。
- 主线状态：✅ 已进入 mainline（约 v6.18-rc1；对应改动如「KVM: x86: Advertise support for the immediate form of MS」）

#### ring-buffer: Allow persistent memory to be user space mmapped
- https://lore.kernel.org/all/20250331143426.947281958@goodmis.org/
- 允许 tracing ring-buffer 使用 reserve_mem 持久内存并映射到用户态，便于跨重启保留 trace。
- 主线状态：✅ 已进入 mainline（约 v6.16-rc1；对应改动如「ring-buffer: Allow reserve_mem persistent ring buffers t」）

#### Implement numa node notifier
- https://lore.kernel.org/all/20250401092716.537512-1-osalvador@suse.de/
- 实现 NUMA 节点通知链，让子系统在 NUMA 节点上/下线时收到回调并作相应处理。
- 主线状态：✅ 已进入 mainline（约 v6.17-rc1；对应改动如「mm,memory_hotplug: implement numa node notifier」）

#### KVM: VM planes
- https://lore.kernel.org/all/20250401161106.790710-1-pbonzini@redhat.com/
- 引入 KVM「VM planes」概念，将虚拟机划分为多个平面以支持更细粒度的隔离与管理。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认


## 2025年 第03期 (Start From 2025/03/01)

#### Add support for a DRM tool like PMU
- https://lore.kernel.org/all/20250326035045.129440-1-irogers@google.com/
- 为 DRM/GPU 提供类似 PMU 的性能监控工具接口，通过 perf 暴露 GPU 相关信息与计数。
- 主线状态：✅ 已进入 mainline（约 v6.18-rc1；对应改动如「perf drm_pmu: Add a tool like PMU to expose DRM informat」）

#### Mediated vPMU 4.0 for x86
- https://lore.kernel.org/all/20250324173121.1275209-1-mizhang@google.com/
- x86 中介式虚拟 PMU（mediated vPMU）第 4 版，让客户机高效直接使用硬件 PMU 计数器。
- 主线状态：✅ 已进入 mainline（；对应改动如「KVM: selftests: Add a helper to query enable_mediated_pm」）

#### Selective KSM: Synchronous and Partitioned Merging
- https://lore.kernel.org/all/20250321173729.3175898-1-souravpanda@google.com/
- 选择性 KSM：支持同步与分区式页合并，精确控制哪些内存参与去重，减少无谓扫描。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Guaranteed CMA
- https://lore.kernel.org/all/20250320173931.1583800-1-surenb@google.com/
- 提供「有保证的」CMA 连续内存分配，确保关键场景下大块连续内存的可用性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Add a Rust GPUVM abstraction
- https://lore.kernel.org/all/20250324-gpuvm-v1-0-7f8213eebb56@collabora.com/
- 为 Rust 驱动提供 GPUVM（GPU 虚拟内存管理）抽象，支撑 Rust 编写的 GPU 驱动。
- 主线状态：✅ 已进入 mainline（；对应改动如「drm/amd/display: Set gpuvm min page size to 4K on dcn35/」）

#### nvme-tcp: Implement TP4129 (KATO Corrections and Clarifications)
- https://lore.kernel.org/all/20250324174909.3919131-1-mkhalfella@purestorage.com/
- 在 nvme-tcp 实现 TP4129，规范 Keep Alive Timeout（KATO）的处理与相关行为澄清。
- 主线状态：✅ 已进入 mainline（；对应改动如「nvme: Use non zero KATO for persistent discovery connect」）

#### virtio_ring in order support
- https://lore.kernel.org/all/20250324054333.1954-1-jasowang@redhat.com/
- 为 virtio_ring 增加 in-order（按序）特性支持，简化并加速按序完成的收发路径。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc3；对应改动如「virtio_ring: add in order support」）

#### Add virtio gpu userptr support
- https://lore.kernel.org/all/20250321080029.1715078-1-honglei1.huang@amd.com/
- 为 virtio-gpu 增加 userptr 支持，允许将用户态内存直接用作 GPU 缓冲区。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### Improve gpu_scheduler trace events + UAPI
- https://lore.kernel.org/all/20250320095818.40622-1-pierre-eric.pelloux-prayer@amd.com/
- 完善 gpu_scheduler 的 trace 事件与相关 UAPI，改进 GPU 调度的可观测性。
- 主线状态：✅ 已进入 mainline（；对应改动如「drm/amdgpu: update trace format to match gpu_scheduler_t」）

#### io_uring: support vectored fixed kernel buffer
- https://lore.kernel.org/all/20250325135155.935398-1-ming.lei@redhat.com/
- 让 io_uring 支持向量化的固定内核缓冲区（vectored fixed kernel buffer），增强注册缓冲的批量 I/O。
- 主线状态：✅ 已进入 mainline（约 v6.15-rc1；对应改动如「io_uring: support vectored kernel fixed buffer」）

#### bpf: add cpu time counter kfuncs
- https://lore.kernel.org/all/20250319163638.3607043-1-vadfed@meta.com/
- 新增读取 CPU 时间计数器的 BPF kfunc，供 BPF 程序精确测量 CPU 时间。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### kexec: introduce Kexec HandOver (KHO)
- https://lore.kernel.org/lkml/20250320015551.2157511-1-changyuanl@google.com/
- 引入 KHO（Kexec HandOver）：kexec 换核时把指定内存/状态原样交接给新内核，支撑热升级。
- 主线状态：✅ 已进入 mainline（约 v7.3-rc1；对应改动如「kernel/kexec_handover.c，KHO 子系统已在主线」）

#### mm: reliable huge page allocator
- https://lore.kernel.org/all/20250313210647.1314586-1-hannes@cmpxchg.org/
- 提供更可靠的大页分配器，降低碎片导致的大页分配失败率，提升大页供给的确定性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rust: add dma coherent allocator abstraction
- https://lore.kernel.org/all/20250317185345.2608976-1-abdiel.janulgue@gmail.com/
- 为 Rust 提供 DMA 一致性内存分配器（CoherentAllocation）抽象，供 Rust 驱动安全申请 DMA 缓冲。
- 主线状态：✅ 已进入 mainline（；对应改动如「rust: dma: remove dma::CoherentAllocation<T>
」）

#### PCI: VF resizable BAR
- https://lore.kernel.org/all/20250312225949.969716-1-michal.winiarski@intel.com/
- 支持 SR-IOV VF 的可调整大小 BAR（resizable BAR），按需配置 VF 的 BAR 大小。
- 主线状态：✅ 已进入 mainline（；对应改动如「PCI/IOV: Skip VF Resizable BAR restore on read error
」）

#### kdump: crashkernel reservation from CMA
- https://lore.kernel.org/all/Z9H10pYIFLBHNKpr@dwarf.suse.cz/
- 让 crashkernel 内存可从 CMA 预留，缓解崩溃内核内存预留对正常可用内存的占用。
- 主线状态：✅ 已进入 mainline（；对应改动如「riscv: kexec_file: Add support for crashkernel CMA reser」）

#### Rust: Add cpumask abstractions
- https://lore.kernel.org/lkml/cover.1742296835.git.viresh.kumar@linaro.org/
- 为 Rust 提供 cpumask 抽象，让 Rust 代码安全地操作 CPU 掩码。
- 主线状态：✅ 已进入 mainline（；对应改动如「rust: cpumask: rename methods of Cpumask for clarity and」）

#### Make ASIDs static for SVM
- https://lore.kernel.org/kvm/20250313215540.4171762-1-yosry.ahmed@linux.dev/
- 为 AMD SEV 安全虚拟机将 ASID 固定/静态分配，简化管理并减少 ASID 切换开销。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### erofs: 48-bit layout support
- https://lore.kernel.org/all/20250310095459.2620647-1-hsiangkao@linux.alibaba.com/
- 为 erofs 增加 48 位布局支持，突破原有寻址上限以支持更大的只读镜像。
- 主线状态：✅ 已进入 mainline（；对应改动如「erofs: handle 48-bit blocks_hi for compressed inodes
」）

#### KSTATE: a mechanism to migrate some part of the kernel state across kexec
- https://lore.kernel.org/all/20250310120318.2124-1-arbn@yandex-team.com/
- KSTATE：在 kexec 换核时迁移部分内核运行态，便于热升级过程中保留状态。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### sched_ext: Enhance built-in idle selection with preferred CPUs
- https://lore.kernel.org/all/20250307200502.253867-1-arighi@nvidia.com/
- 增强 sched_ext 内建空闲 CPU 选择，支持「首选 CPU」以改进任务放置与局部性。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### tcp: scale connect() under pressure
- https://lore.kernel.org/all/20250302124237.3913746-1-edumazet@google.com/
- 优化高压力下 TCP connect() 的可扩展性，缓解端口/锁竞争导致的连接建立瓶颈。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### rust: configfs abstractions
- https://lore.kernel.org/all/20250227-configfs-v5-0-c40e8dc3b9cd@kernel.org/
- 为内核 configfs 提供 Rust 抽象，让 Rust 驱动能创建可配置的 configfs 层级结构。
- 主线状态：✅ 已进入 mainline（；对应改动如「MAINTAINERS: configfs: split configfs entry in C and Rus」）

#### erofs: inode page cache share feature
- https://lore.kernel.org/all/20250301145002.2420830-1-hongzhen@linux.alibaba.com/
- 为 erofs 增加 inode 页缓存共享特性，多个引用同一数据的 inode 共享页缓存以节省内存。
- 主线状态：✅ 已进入 mainline（；对应改动如「erofs: implement .fadvise for page cache share
」）

#### cxl: support CXL memory RAS features
- https://lore.kernel.org/all/20250320180450.539-1-shiju.jose@huawei.com/
- 为 CXL 内存增加 RAS（可靠性/可用性/可服务性）特性支持，如错误上报与处理。
- 主线状态：✅ 已进入 mainline（；对应改动如「cxl/pci: Fix appropriate checking for _OSC while handlin」）

#### cgroup v1 deprecation warnings
- https://lore.kernel.org/all/20250304153801.597907-1-mkoutny@suse.com/
- 为 cgroup v1 增加弃用告警，提示用户逐步迁移到 cgroup v2。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

#### pidfs: provide information after task has been reaped
- https://lore.kernel.org/all/20250305-work-pidfs-kill_on_last_close-v3-0-c8c3d8361705@kernel.org/
- 让 pidfs 在任务被回收（reaped）后仍能提供其信息，便于可靠获取已退出进程的元数据。
- 主线状态：✅ 已进入 mainline（；对应改动如「fanotify: allow reporting pidfds for reaped tasks
」）

#### ftrace: Add function arguments to function tracers
- https://lore.kernel.org/all/20250227185804.639525399@goodmis.org/
- 让 function tracer 能记录函数参数，增强函数级 tracing 的信息量。
- 主线状态：✅ 已进入 mainline（；对应改动如「ftrace: Add support for function argument to graph trace」）

#### x86/resctrl telemetry monitoring
- https://lore.kernel.org/all/20250303233340.333743-1-tony.luck@intel.com/
- 为 x86 resctrl 增加遥测监控能力，读取并暴露更多硬件遥测事件（如能耗/带宽）。
- 主线状态：✅ 已进入 mainline（；对应改动如「x86,fs/resctrl: Update documentation for telemetry event」）

#### x86: Support Intel Advanced Performance Extensions
- https://lore.kernel.org/all/20250320234301.8342-1-chang.seok.bae@intel.com/
- 为 x86 增加 Intel APX（高级性能扩展，扩展通用寄存器等）支持，涉及上下文/信号处理适配。
- 主线状态：✅ 已进入 mainline（约 v6.16-rc1；commit 引用了本系列 Link）

#### Add a percpu subsection for hot data
- https://lore.kernel.org/all/20170307092431.15198-1-diaconita.tamara@gmail.com/
- 为 per-CPU 数据新增热数据子段，将高频访问的 per-CPU 变量按缓存行聚集以改善局部性。
- 主线状态：✅ 已进入 mainline（；对应改动如「percpu: align percpu readmostly subsection to cacheline
」）

#### sched/fair: Defer CFS throttling to exit to user mode
- https://lore.kernel.org/all/20250220093257.9380-1-kprateek.nayak@amd.com/
- 将 CFS 带宽限流延迟到返回用户态时执行，避免在内核持锁/关键区被限流引发的问题。
- 主线状态：❔ 未自动检索到合入记录（截至主线 v7.3-rc4，2026-09-23）；可能为 RFC/评审中，或已以改版合入，需人工确认

