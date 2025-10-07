//#include <stdio.h>
//
//int main() {
//    int count = 0; // 用于统计符合条件的三位数的数量
//    printf("符合条件的三位数有：\n");
//
//    for (int i = 1; i <= 4; i++) { // 百位
//        for (int j = 1; j <= 4; j++) { // 十位
//            for (int k = 1; k <= 4; k++) { // 个位
//                if (i != j && i != k && j != k) { // 确保三个位置的数字互不相同
//                    printf("%d%d%d\n", i, j, k);
//                    count++;
//                }
//            }
//        }
//    }
//
//    printf("总共有 %d 个互不相同且无重复数字的三位数。\n", count);
//    return 0;
//}
