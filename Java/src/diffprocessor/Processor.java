package diffprocessor;

/**
 * Created by VavilauA on 6/19/2015.
 */
public class Processor {
    private final long limit;

    public Processor(long limit) {
        // TODO: initialize.
        this.limit = limit;
    }

    public void doProcess(SortedLimitedList<Double> mustBeEqualTo, SortedLimitedList<Double> expectedOutput) {
        // TODO: make "mustBeEqualTo" list equal to "expectedOutput".
        // 0. Processor will be created once and then will be used billion times.
        // 1. Use methods: AddFirst, AddLast, AddBefore, AddAfter, Remove to modify list.
        // 2. Do not change expectedOutput list.
        // 3. At any time number of elements in list could not exceed the "Limit".
        // 4. "Limit" will be passed into Processor's constructor. All "mustBeEqualTo" and "expectedOutput" lists will have the same "Limit" value.
        // 5. At any time list elements must be in non-descending order.
        // 6. Implementation must perform minimal possible number of actions (AddFirst, AddLast, AddBefore, AddAfter, Remove).
        // 7. Implementation must be fast and do not allocate excess memory.

        /**
         * Java implementation of the method by AnriShitsko
         */

        // initialize
        SortedLimitedList.Entry<Double> modifiedEntry = mustBeEqualTo.getFirst();
        SortedLimitedList.Entry<Double> expectedEntry = expectedOutput.getFirst();

        // if-block to remove all entries from the mustBeEqualTo if the expectedOutput is empty
        if (expectedEntry == null) {
            while (mustBeEqualTo.getCount() > 0)
                mustBeEqualTo.remove(mustBeEqualTo.getFirst());
        }

        while (expectedEntry != null) {
            // if-block to add entries to the mustBeEqualTo if both lists completely or almost different
            if (modifiedEntry == null)
                mustBeEqualTo.addAfter(modifiedEntry, expectedEntry.getValue());

            // if-block to remove entry from the mustBeEqualTo
            else if (modifiedEntry.getValue() < expectedEntry.getValue()) {
                mustBeEqualTo.remove(modifiedEntry);
                modifiedEntry = mustBeEqualTo.getFirst();
                expectedEntry = expectedOutput.getFirst();
                continue;

            // if-block to add entry to the mustBeEqualTo
            } else if (modifiedEntry.getValue() > expectedEntry.getValue()) {

                // if-block to remove entry if both lists have current entry the last
                if (modifiedEntry.getNext() == null && expectedEntry.getNext() == null) {
                    mustBeEqualTo.remove(modifiedEntry);
                    modifiedEntry = mustBeEqualTo.getLast();
                    expectedEntry = expectedOutput.getLast();
                    mustBeEqualTo.addLast(expectedEntry.getValue());

                // else to add entry to the mustBeEqualTo
                } else
                    mustBeEqualTo.addBefore(modifiedEntry, expectedEntry.getValue());

                // if-block to remove excess entries if the mustBeEqualTo list have all necessary entries
                if ((expectedEntry = expectedEntry.getNext()) == null) {
                    int countElementToRemove = mustBeEqualTo.getCount() - expectedOutput.getCount();
                    while (countElementToRemove-- != 0)
                        mustBeEqualTo.remove(mustBeEqualTo.getLast());
                }
                continue;
            }

            // get the next entry of the modifiedEntry
            if (modifiedEntry != null) {
                modifiedEntry = modifiedEntry.getNext();
            }

            // get the next entry of the expectedEntry
            expectedEntry = expectedEntry.getNext();
        }
    }
}
