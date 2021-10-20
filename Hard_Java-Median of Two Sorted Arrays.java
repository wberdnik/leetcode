//https://leetcode.com/problems/median-of-two-sorted-arrays/
 /**
     * @param {number[]} nums1
     * @param {number[]} nums2
     * @return {number}
     * @throw 'empty arrays'
     */
    var findMedianSortedArrays = function (nums1, nums2) {
        // частные случаи
        const ln1 = nums1.length, ln2 = nums2.length;
        if (!ln1 && !ln2) // assert
            throw 'empty arrays'

        // динамическое программирование
        const median1 = fastMedian(nums1, []),
            median2 = fastMedian(nums2, [])

        if (median1 === median2) {// медианы по отсортированному делать посередине al+bl=ar+br
            return median1;
        }

        if (!ln1) return median2;
        else if (!ln2) return median1;
        // паровозики
        if (nums1[0] <= nums2[0] && nums1[ln1 - 1] <= nums2[0]) {
            return fastMedian(nums1, nums2)
        }
        if (nums2[0] <= nums1[0] && nums2[ln2 - 1] <= nums1[0]) {
            return fastMedian(nums2, nums1)
        }

        const MedianOfMedian = (median1 + median2) / 2

        let mInfPos, mSupPos
        const x1InxMM = foundEqInx(nums1, 0, ln1, MedianOfMedian),
         x2InxMM = foundEqInx(nums2, 0, ln2, MedianOfMedian)
        let x1PosMM = x1InxMM == undefined ? ln1 : x1InxMM ,
           x2PosMM = x2InxMM == undefined ? ln2 : x2InxMM // Захват чуть больших элементов ведет к рассортировке окна


        if ((ln1 + ln2) % 2) {
            mInfPos = mSupPos = (ln1 + ln2 + 1) / 2
        } else {
            mInfPos = (ln1 + ln2) / 2
            mSupPos = mInfPos + 1
        }
        while (x1PosMM + x2PosMM != mInfPos) {
            if ((x1PosMM + x2PosMM) > mInfPos) { // Назад
                backward()
            } else { //Вперед
                forward()
            }
        }

        let inf = fetchVal42()

        if (mInfPos != mSupPos) {
            forward()
            return (inf + fetchVal42()) / 2
        }
        return inf;


        function backward() {
            const sortObjects = [];


            if (x1PosMM) {
                sortObjects.push({name: 'x1', val: nums1[x1PosMM - 1]})
            }
            if (x2PosMM) {
                sortObjects.push({name: 'x2', val: nums2[x2PosMM - 1]})
            }

            if (x1PosMM > 1) {
                sortObjects.push({name: 'x1', val: nums1[x1PosMM - 2]})
            }
            if (x2PosMM > 1) {
                sortObjects.push({name: 'x2', val: nums2[x2PosMM - 2]})
            }

            sortObjects.sort((a, b) => {
                if (a.val > b.val) return 1;
                if (a.val == b.val) return 0;
                if (a.val < b.val) return -1;
            })

            if (sortObjects.pop().name == 'x1') {
                x1PosMM--;
            } else
                x2PosMM--;
        }

        function forward() {
            const sortObjects = [];

            if (x1PosMM < ln1) {
                sortObjects.push({name: 'x1', val: nums1[x1PosMM]})
            }
            if (x2PosMM < ln2) {
                sortObjects.push({name: 'x2', val: nums2[x2PosMM]})
            }

            sortObjects.sort((a, b) => {
                if (a.val > b.val) return 1;
                if (a.val == b.val) return 0;
                if (a.val < b.val) return -1;
            })

            if (sortObjects.shift().name == 'x1') {
                x1PosMM++;
            } else
                x2PosMM++;
        }

        function fetchVal42() {
            if (x1PosMM > 0 && x2PosMM > 0) {
                return Math.max(nums1[x1PosMM - 1], nums2[x2PosMM - 1])
            } else if (x1PosMM > 0) {
                return nums1[x1PosMM - 1]
            } else if (x2PosMM > 0) {
                return nums2[x2PosMM - 1]
            } else throw 'smoke'

        }

        // Ищем через дихотомию синхронизацию одного массива в другом
        // O(log(n))
        function foundEqInx(nums, stInx, ln, xVal) {
            if (ln - stInx < 1)
                return -1
            if (ln - stInx < 6) {

                if (ln - stInx == 1 || nums[stInx] >= xVal) {
                    return stInx
                }
                if (ln - stInx == 2 || nums[stInx + 1] >= xVal) {
                    return stInx + 1
                }
                if (ln - stInx == 3 || nums[stInx + 2] >= xVal) {
                    return stInx + 2
                }
                if (ln - stInx == 4 || nums[stInx + 3] >= xVal) {
                    return stInx + 3
                }
                if (ln - stInx == 5 || nums[stInx + 4] >= xVal) {
                    return stInx + 4
                }
            }

            const pivotInx = stInx + Math.floor((ln - stInx) / 2);
            if (nums[pivotInx] > xVal && (ln - pivotInx) > 0) {
                return foundEqInx(nums, stInx, pivotInx + 1, xVal)
            }

            if (nums[pivotInx] < xVal && (pivotInx + 1 - stInx) > 0) {
                return foundEqInx(nums, pivotInx, ln, xVal)
            }

            return pivotInx

        }

        // извлекает медиану, когда массивы паровозиком
        // O(0)
        function fastMedian(first, second) {
            const ln1 = first.length, ln2 = second.length
            if ((ln1 + ln2) == 0) return undefined;
            let mInfInx, mSupInx

            if ((ln1 + ln2) % 2) {
                mInfInx = mSupInx = (ln1 + ln2 + 1) / 2 - 1
            } else {
                mInfInx = (ln1 + ln2) / 2 - 1
                mSupInx = mInfInx + 1
            }
            const inf = mInfInx >= ln1 ? second[mInfInx - ln1] : first[mInfInx],
                sup = mSupInx >= ln1 ? second[mSupInx - ln1] : first[mSupInx]
            return (inf + sup) / 2;
        }

    };
