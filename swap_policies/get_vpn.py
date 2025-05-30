vaddr = open("output_address_ls.txt", "r")
vpage = open("output_page_ls.txt", "w")

lines = vaddr.readlines()
VPN_MASK = 0xfffff000 # first 12-bits are offset in x86-64 Intel Core processors (when doing 2-page level page mode)
for line in lines:
    vpn = int("0x" + line.strip(), 16) & VPN_MASK >> 12
    vpage.write(f"{vpn}\n")
vaddr.close()
vpage.close()
