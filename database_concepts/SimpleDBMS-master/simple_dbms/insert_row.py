

            elif curr_col_type == 3:                        # if varchar
                byte_array = bytearray(offset)            # convert to byte array
                for i in range(0, len(byte_array)):
                    self._key.write_byte(byte_array[i])

                self._data.write_int(offset)
                offset += len(self._values[i])from data_output_stream import DataOutputStream
from column import Column


class InsertRow:
    # Constants for special offsets
    # The field with this offset is a primary key.
    IS_PKEY = -1

    # The field with this offset has a null value.
    IS_NULL = -2

    def __init__(self, table, values):
        """
        Constructs an InsertRow object for a row containing the specified
        values that is to be inserted in the specified table.
        :param table:
        :param values:
        """
        self._table = table
        self._values = values

        # These objects will be created by the marshall() method.
        self._key = None
        self._data = None

    def marshall(self):
        """
        Takes the collection of values for this InsertRow
        and marshalls them into a key/data pair.
        :return:
        """

        self._data = DataOutputStream()
        self._key = DataOutputStream()
        pkey = self._table.primary_key_column()
        pkey_it = 0

        # write key value to stream
        for i in range(0, self._table.num_columns()):
            col = self._table.get_column(i)
            if col.is_primary_key() == True:
                pkey_it = i

        pk_type = pkey.get_type()

        if pkey == None:                                    # if null
            self._key.write_int(self.IS_NULL)

        elif pk_type == 0:                                  # if int
            self._key.write_int(self._values[pkey_it])

        elif pk_type == 1:                                  # if real
            self._key.write_float(self._values[pkey_it])

        elif pk_type == 2:                                  # if char
            byte_array = bytearray(self._values[pkey_it])   # convert to byte array
            for i in range(0, len(byte_array)):
                self._key.write_byte(byte_array[i])

        elif pk_type == 3:                                  # if varchar
            byte_array = bytearray(self._values[pkey_it])   # convert to byte array
            for i in range(0, len(byte_array)):
                self._key.write_byte(byte_array[i])

        num_offsets = self._table.num_columns() + 1         # number of offsets
        offset = num_offsets * 4                            # initialize data offset

        # write data offsets and values to stream
        for i in range(0, self._table.num_columns()):

            curr_col = self._table.get_column(i)
            curr_col_type = curr_col.get_type()

            if i == pkey_it:                                # if primary key
                self._data.write_int(self.IS_PKEY)

            elif self._values[i] == None:                   # if null
                self._data.write_int(self.IS_NULL)

            elif curr_col_type == 0:                        # if int
                self._data.write_int(offset)
                offset += curr_col.get_length()

            elif curr_col_type == 1:                        # if real
                self._data.write_int(offset)
                offset += curr_col.get_length()

            elif curr_col_type == 2:                        # if char
                self._data.write_int(offset)
                offset += curr_col.get_length()

            elif curr_col_type == 3:                        # if varchar
                self._data.write_int(offset)
                offset += len(self._values[i])

        # write data to stream
        for i in range(0, self._table.num_columns()):

            if i != pkey_it:

                curr_col = self._table.get_column(i)
                curr_col_type = curr_col.get_type()

                if curr_col == None:                                # if null
                    self._key.write_int(self.IS_NULL)

                elif curr_col_type == 0:                            # if int
                    self._key.write_int(self._values[i])

                elif curr_col_type == 1:                            # if real
                    self._key.write_float(self._values[i])

                elif curr_col_type == 2:                            # if char
                    byte_array = bytearray(self._values[i])   # convert to byte array
                    for j in range(0, len(byte_array)):
                        self._key.write_byte(byte_array[j])

                elif curr_col_type == 3:                            # if varchar
                    byte_array = bytearray(self._values[i])   # convert to byte array
                    for j in range(0, len(byte_array)):
                        self._key.write_byte(byte_array[j])

    def get_key(self):
        """
        Returns the key in the key/data pair for this row.
        :return: the key
        """
        return self._key

    def get_data(self):
        """
        Returns the data item in the key/data pair for this row.
        :return: the data
        """
        return self._data