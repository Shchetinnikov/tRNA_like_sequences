<template>
    <div>
        <select class="form-select" @change="changeOption">
        <option disabled value="">Choose from list</option>
        <option
            v-for="option in options"
            :key="option.value"
            :value="option.value"
        >
            {{ option.name }}
        </option>
        </select>
    </div>
  </template>
  
  <script>
  export default {
    name: 'my-select',
    props: {
      modelValue: {
        type: String
      },
      options: {
        type: Array,
        default: () => []
      }
    },
    methods: {
      changeOption(event) {
        this.$emit('update:modelValue', event.target.value);
      }
    }
  }
  </script>
  
  <style scoped>
  </style>